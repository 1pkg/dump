#include "Director.hpp"
#include "GameAct/Act.hpp"
#include "Chunk.hpp"
#include "Level.hpp"
#include "GameAct/Objects/Object.hpp"
#include "GameAct/Objects/SubTypes/CompositeObject.hpp"
#include "GameAct/Objects/Factories/ObjectsFactory.hpp"
#include "Resources/Cache/Cache.hpp"

namespace GameAct
{

Chunk::Chunk( int chunkIndex  )
	: _chunkIndex( chunkIndex )
{
}

Chunk::~Chunk() // for uniq_ptr
{
}

int
Chunk::getChunkIndex() const
{
	return _chunkIndex;
}

cocos2d::Layer *
Chunk::getLayer()
{
	return Director::getInstance().getGameAct()->getLevel()->getLayer();
}

Object *
Chunk::getObjectByBody( cocos2d::PhysicsBody * body )
{
	auto getObjByBody = [ body ]( Object * obj )->Object *
	{
		if( ! obj->isComposed() )
		{
			if( obj->getBody() == body )
				return obj;
		}
		else
		{
			auto compositeObject = dynamic_cast< CompositeObject * > ( obj );
			auto set = compositeObject->getObjects();
			for( auto compObj : set )
				if( compObj->getBody() == body )
					return compObj;
		}

		return nullptr;
	};

	for(
		std::vector< std::unique_ptr< Object > >::iterator it = _objects.begin();
		it != _objects.end();
		++it
	)
	{
		auto obj = getObjByBody( it->get() );
		if( obj )
			return obj;
	}

	return nullptr;
}

void
Chunk::addObject( Object * object )
{
	_objects.push_back( std::unique_ptr< Object > ( object ) );
}

Object *
Chunk::createObject( const Resources::ObjectInfo & info )
{
	const ObjectsFactory * factory =  Director::getInstance().getGameAct()->getObjectsFactory();

	auto level = Director::getInstance().getGameAct()->getLevel();
	Resources::LevelOrientation orientation = level->getLevelOrientation();
	cocos2d::Size size = level->getLevelSize();

	float height = size.height;
	float width = size.width;
	float deltaY = orientation == Resources::LevelOrientation::Vertical
	? height * _chunkIndex - height
	: 0.0f;
	float deltaX = orientation == Resources::LevelOrientation::Horizontal
	? width * _chunkIndex - width
	: 0.0f;

	Object * object = factory->create( info.name );

	if( !object )
		throw std::exception();

	object->setAdditionalParam( info.additionalParam );

	object->setRotation( info.angle );

	object->setSize(
		cocos2d::Size( info.size.width * width, info.size.height * height )
	);

	object->setScale( info.scale );

	object->setPosition(
		cocos2d::Vec2( info.position.x * width + deltaX, info.position.y * height - deltaY )
	);

	object->setMask( info.mask );
	object->setColideMask( info.collideMask );
	object->setContactMask( info.contactMask );

	for( auto slave : info.slaves )
		object->addSlave( createObject( slave ) );

	object->attachToChunk( *this, info.zIndex );

	object->runAction( info.initAction );

	return object;
}

Chunk *
Chunk::create( int index )
{
	if( Resources::Cache::getInstance().getChunksCount() == index )
		return nullptr;

	const auto & chunkInfo = Resources::Cache::getInstance().getChunkInfo( index );

	Chunk * chunk = new Chunk( index );

	Resources::ObjectInfo edge;
	edge.name = "Edge";
	edge.size = cocos2d::Size( 1.0f, 1.0f );
	edge.position = cocos2d::Vec2( 0.5f, 0.5f );
	edge.mask = 0x2;
	edge.collideMask = 0x0;
	edge.contactMask = 0x4;
	edge.zIndex = 0;
	auto edgeObj = chunk->createObject( edge );

	for( Resources::ObjectInfo info : chunkInfo )
		chunk->createObject( info );

	return chunk;
}

}