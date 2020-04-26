#include "Director.hpp"
#include "GameAct/Act.hpp"
#include "Level.hpp"
#include "Chunk.hpp"
#include "GameAct/Objects/Object.hpp"
#include "GameAct/Objects/SubTypes/LongObject.hpp"
#include "GameAct/Objects/SubTypes/CompositeLongObject.hpp"
#include "GameAct/Objects/Factories/ObjectsFactory.hpp"
#include "Resources/Cache/Cache.hpp"

namespace GameAct
{

Level *
Level::create( cocos2d::Layer * layer, cocos2d::PhysicsWorld * physicWorld )
{
	return new Level( layer, physicWorld );
}

Level::Level( cocos2d::Layer * layer, cocos2d::PhysicsWorld * physicWorld )
	: _layer( layer ),
	_physicWorld( physicWorld )
{
}

int Level::initialize()
{
	// setting physical sheduler, for contact processing
	_physicListener = cocos2d::EventListenerPhysicsContact::create();
	_physicListener->onContactBegin = [ this ]( cocos2d::PhysicsContact& contact )
	{
		cocos2d::PhysicsBody* bodyA = contact.getShapeA()->getBody();
		cocos2d::PhysicsBody* bodyB = contact.getShapeB()->getBody();
		return this->contact( bodyA, bodyB );
	};
	_physicListener->onContactSeperate = [ this ]( cocos2d::PhysicsContact& separate )
	{
		cocos2d::PhysicsBody* bodyA = separate.getShapeA()->getBody();
		cocos2d::PhysicsBody* bodyB = separate.getShapeB()->getBody();
		this->separate( bodyA, bodyB );
	}; 
	_layer->getEventDispatcher()->addEventListenerWithSceneGraphPriority( _physicListener, _layer );
	_layer->schedule( std::bind( &Level::step, this ), 1.0f, "PhysicScheduler" );

	//  setting default long objects
	getPhysicWorld()->setGravity( getLevelGravity() );

	const ObjectsFactory * factory =  Director::getInstance().getGameAct()->getObjectsFactory();
	cocos2d::Size size = getLevelSize();

	// background
	_backGround = Resources::Cache::getInstance().getObjectRepresentation( "BackGround" );

	float xScale = size.width / _backGround->getContentSize().width;
	float yScale = size.height / _backGround->getContentSize().width;

	_backGround->setScaleX( xScale );
	_backGround->setScaleY( yScale );

	_backGround->setPosition( cocos2d::Vec2( size.width / 2.0f, size.height / 2.0f ) );
	//getLayer()->addChild( _backGround, 0 );

	_backGround->runAction( cocos2d::Follow::create( getLayer() ) );

	// character
	LongObject * character = dynamic_cast< LongObject * > ( factory->create( "Character" ) );
	character->setSize( cocos2d::Size( size.width * 0.075f, size.height * 0.15f ) );
	character->setPosition( cocos2d::Vec2( size.width * 0.5f, size.height * 0.5f ) );
	character->attachToLevel( * this, 3 );
	_longObjects.push_back( std::unique_ptr< LongObject > ( character ) );

	return 0;
}

Level::~Level()
{
	_backGround->removeFromParentAndCleanup( true );
	_layer->unschedule( "PhysicScheduler" );
	_layer->getEventDispatcher()->removeEventListener( _physicListener );
}

cocos2d::Layer *
Level::getLayer() const
{
	return _layer;
}

cocos2d::PhysicsWorld *
Level::getPhysicWorld() const
{
	return _physicWorld;
}

unsigned int
Level::getChunksCount() const
{
	return Resources::Cache::getInstance().getChunksCount();
}

Resources::LevelOrientation
Level::getLevelOrientation() const
{
	return Resources::Cache::getInstance().getLevelOrientation();
}

std::string
Level::getLevelName() const
{
	return Resources::Cache::getInstance().getLevelName();
}

cocos2d::Size
Level::getLevelSize() const
{
	auto size = cocos2d::Director::getInstance()->getVisibleSize();
	float universal = ( size.width + size.height ) / 2.0f;
	float width = universal * Resources::Cache::getInstance().getLevelSize().width;
	float height = universal * Resources::Cache::getInstance().getLevelSize().height;
	return cocos2d::Size( width, height );
}

cocos2d::Vec2
Level::getLevelGravity() const
{
	return Resources::Cache::getInstance().getLevelGravity();
}

cocos2d::Size
Level::getVisibleSize() const
{
	return cocos2d::Director::getInstance()->getVisibleSize();
}

void
Level::addObject( LongObject * object )
{
	_longObjects.push_back( std::unique_ptr< LongObject > ( object ) );
}

void
Level::updateChunks()
{
	int index =
		_nextChunk
	?	_nextChunk->getChunkIndex() + 1
	:	initialize();

	Chunk * chunk = Chunk::create( index );
	if( !chunk )
	{
		Director::getInstance().finishAct();
		return;
	}

	_prevChunk.reset( _currentChunk.release() );
	_currentChunk.reset( _nextChunk.release() );
	_nextChunk.reset( chunk );
}

bool
Level::contact( cocos2d::PhysicsBody * objl, cocos2d::PhysicsBody * objr )
{
	Contact contact = find( objl, objr );

	if( ( std::find( _contacts.begin(), _contacts.end(), contact ) != _contacts.end() ) )
		return false;

	//if( contact.pair.first && contact.pair.second )
	return contact.pair.first->beginContact( contact.pair.second )
	? _contacts.push_back( contact ), true
	: false;
}

void
Level::step()
{
	for( Contact contact : _contacts )
		contact.pair.first->stepContact( contact.pair.second );
}

void
Level::separate( cocos2d::PhysicsBody * objl, cocos2d::PhysicsBody * objr )
{
	Contact contact = find( objl, objr );

	if( ( std::find( _contacts.begin(), _contacts.end(), contact ) == _contacts.end() ) )
		return;

	_contacts.erase( std::remove( _contacts.begin(), _contacts.end(), contact ) );

	contact.pair.first->separateContact( contact.pair.second );
}

Level::Contact
Level::find( cocos2d::PhysicsBody * objl, cocos2d::PhysicsBody * objr )
{
	Contact result = Contact( { nullptr, nullptr } );

	Object * obj1 = getLongObjectByBody( objl );
	if( !obj1 )
		obj1 = _currentChunk->getObjectByBody( objl );
	if( !obj1 && _prevChunk )
		obj1 = _prevChunk->getObjectByBody( objl );
	if( !obj1 && _nextChunk )
		obj1 = _nextChunk->getObjectByBody( objl );

	Object * obj2 = getLongObjectByBody( objr );
	if( !obj2 )
		obj2 = _currentChunk->getObjectByBody( objr );
	if( !obj2 && _prevChunk )
		obj2 = _prevChunk->getObjectByBody( objr );
	if( !obj2 && _nextChunk )
		obj2 = _nextChunk->getObjectByBody( objr );

	result.pair.first = obj1;
	result.pair.second = obj2;

	return result;
}

LongObject *
Level::getLongObjectByBody( cocos2d::PhysicsBody * body )
{
	auto getLongObjByBody = [ body ]( LongObject * obj )->LongObject *
	{
		if( ! obj->isComposed() )
		{
			if( obj->getBody() == body )
				return obj;
		}
		else
		{
			auto compositeLongObject = dynamic_cast< CompositeLongObject * > ( obj );
			auto set = compositeLongObject->getObjects();
			for( auto compLongObj : set )
				if( compLongObj->getBody() == body )
					return compLongObj;
		}

		return nullptr;
	};

	for(
		auto it = _longObjects.begin();
		it != _longObjects.end();
		++it
	)
	{
		auto obj = getLongObjByBody( it->get() );
		if( obj )
			return obj;
	}

	return nullptr;
}

}