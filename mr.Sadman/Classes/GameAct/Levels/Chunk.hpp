#ifndef __GAME_ACT_CHUNK_HPP__
#define __GAME_ACT_CHUNK_HPP__

#include "Resources/Forward.hpp"

#include "ThirdParty/noncopyable.hpp"

#include <cocos2d.h>

#include <vector>
#include <memory>

namespace GameAct
{

class Object;

class Chunk :
	public ThirdParty::noncopyable
{
public:

	static Chunk * create( int chunkIndex );

	~Chunk();

	int getChunkIndex() const;	
	cocos2d::Layer * getLayer();
	Object * getObjectByBody( cocos2d::PhysicsBody * body );

	void addObject( Object * object );

private:

	Object * createObject( const Resources::ObjectInfo & info );

	Chunk( int chunkIndex );

	int _chunkIndex;

	std::vector< std::unique_ptr< Object > > _objects;
};

}

#endif