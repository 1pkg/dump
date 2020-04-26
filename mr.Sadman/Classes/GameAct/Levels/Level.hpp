#ifndef __GAME_ACT_LEVEL_HPP__
#define __GAME_ACT_LEVEL_HPP__

#include "ThirdParty/noncopyable.hpp"

#include <cocos2d.h>

#include <vector>
#include <memory>

namespace GameAct
{

class Object;
class LongObject;

class Chunk;

class Level
	: public ThirdParty::noncopyable
{
public:

	static Level * create( cocos2d::Layer * layer, cocos2d::PhysicsWorld * physicWorld );

	~Level();

	cocos2d::Layer * getLayer() const;
	cocos2d::PhysicsWorld * getPhysicWorld() const;

	unsigned int getChunksCount() const;

	std::string getLevelName() const;
	Resources::LevelOrientation getLevelOrientation() const;
	cocos2d::Size getLevelSize() const;
	cocos2d::Vec2 getLevelGravity() const;

	cocos2d::Size getVisibleSize() const;

	void addObject( LongObject * object );

	void updateChunks();

public:

	struct Contact
	{
		std::pair< Object *, Object * > pair;

		Contact( std::pair< Object *, Object * > p )
		{
			pair = p;
		}

		bool operator ==( const Contact & contact ) const
		{
			return ( pair.first == contact.pair.first && pair.second == contact.pair.second )
				|| ( pair.first == contact.pair.second && pair.second == contact.pair.first );
		}
	};

private:

	Contact find( cocos2d::PhysicsBody * objl, cocos2d::PhysicsBody * objr );

	bool contact( cocos2d::PhysicsBody * objl, cocos2d::PhysicsBody * objr );
	void step();
	void separate( cocos2d::PhysicsBody * objl, cocos2d::PhysicsBody * objr );

	std::vector< Contact > _contacts;
	cocos2d::EventListenerPhysicsContact * _physicListener;

private:

	Level( cocos2d::Layer * layer, cocos2d::PhysicsWorld * physicWorld );

	int initialize();

	LongObject * getLongObjectByBody( cocos2d::PhysicsBody * body );
	
	cocos2d::Layer * _layer;
	cocos2d::PhysicsWorld * _physicWorld;

	std::unique_ptr< Chunk > _prevChunk;
	std::unique_ptr< Chunk > _currentChunk;
	std::unique_ptr< Chunk > _nextChunk;

	std::vector< std::unique_ptr< LongObject > > _longObjects; // their lifetime == levels lifetime

	cocos2d::Node * _backGround;
};

}

#endif