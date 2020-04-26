#include "Object.hpp"
#include "GameAct/Levels/Chunk.hpp"
#include "Resources/Cache/Cache.hpp"

namespace GameAct
{

Object::~Object()
{
	if( _representation && getBody() )
		getBody()->removeFromWorld();

	if( _representation )
		_representation->removeFromParentAndCleanup( true );

	if( _audio )
		_audio->release();
}

void
Object::initialize()
{
	_representation = Resources::Cache::getInstance().getObjectRepresentation( getResourcesName() );

	auto body = Resources::Cache::getInstance().getObjectBody( getResourcesName() );
	if( body )
		_representation->setPhysicsBody( body );

	_audio = Resources::Cache::getInstance().getObjectAudio( getResourcesName() );

	_master = nullptr;
}

cocos2d::Size
Object::getSize() const
{
	return _representation->getBoundingBox().size;
}

cocos2d::Size
Object::getContentSize() const
{
	return _representation->getContentSize();
}

cocos2d::Vec2
Object::getPosition() const
{
	return _representation->getPosition();
}

std::string
Object::getStatus() const
{
	return _status;
}

cocos2d::PhysicsBody *
Object::getBody() const
{
	return _representation->getPhysicsBody();
}

ThirdParty::Audio *
Object::getAudio() const
{
	return _audio;
}

bool
Object::isComposed() const
{
	return false;
}

bool
Object::isLongObject() const
{
	return false;
}

void
Object::setPosition( cocos2d::Vec2 position )
{
	_representation->setPosition( position );
}

void
Object::setSize( cocos2d::Size size )
{
	cocos2d::Size spriteSize = _representation->getContentSize();
	float xScale = size.width / spriteSize.width;
	float yScale = size.height / spriteSize.height;

	_representation->setScaleX( xScale );
	_representation->setScaleY( yScale );
}

void
Object::setAdditionalParam( std::string additionalParam )
{
	return;
}

void
Object::setRotation( float angle )
{
	getBody() ?
	_representation->runAction( cocos2d::RotateBy::create( 0.0f, angle ) )
	: _representation->setRotation( angle );
}

void
Object::setScale( cocos2d::Vec2 scale )
{
	getBody() ?
	_representation->runAction( cocos2d::ScaleBy::create( 0.0f, scale.x, scale.y ) )
	: _representation->setScaleX( scale.x ), _representation->setScaleY( scale.y );
}

void
Object::setMask( int mask )
{
	if( getBody() )
		getBody()->setCategoryBitmask( mask );
}

void
Object::setColideMask( int colideMask )
{
	if( getBody() )
		getBody()->setCollisionBitmask( colideMask );
}

void
Object::setContactMask( int contactMask )
{
	if( getBody() )
		getBody()->setContactTestBitmask( contactMask );
}

void
Object::addSlave( Object * slave )
{
	_slaves.push_back( slave );
	slave->_master = this;
}

void
Object::hide()
{
	_representation->setVisible( false );
	if( getBody() )
		getBody()->setEnable( false );
}

void
Object::show()
{
	_representation->setVisible( true );
	if( getBody() )
		getBody()->setEnable( true );
}

void
Object::attachToChunk( Chunk & chunk, int zIndex )
{
	_chunk = &chunk;

	chunk.addObject( this );

	chunk.getLayer()->addChild( _representation, zIndex );
}

void
Object::runAction( const std::string & action )
{
	return;
}

bool
Object::beginContact( Object * object )
{
	// object->startInteract( this );
	return true;
}

void
Object::stepContact( Object * object )
{
	// object->stepInteract( this );
	return;
}

void
Object::separateContact( Object * object )
{
	// object->stopInteract( this );
	return;
}

}