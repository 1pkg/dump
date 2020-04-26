#ifndef __GAME_ACT_LONG_OBJECT_HPP__
#define __GAME_ACT_LONG_OBJECT_HPP__

#include "GameAct/Objects/Object.hpp"

namespace GameAct
{

class Level;

class LongObject
	: public Object
{
public:

	bool isLongObject() const override;

	void attachToChunk( Chunk & chunk, int zIndex ) override;
	virtual void attachToLevel( Level & level, int zIndex );

private:

	Level * _level;
};

}

#endif
