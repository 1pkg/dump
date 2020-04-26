#include "LongObject.hpp"
#include "GameAct/Levels/Level.hpp"

namespace GameAct
{

bool
LongObject::isLongObject() const
{
	return true;
}

void
LongObject::attachToChunk( Chunk & chunk, int zIndex )
{
	return;
}

void
LongObject::attachToLevel( Level & level, int zIndex )
{
	_level = &level;

	level.addObject( this );
	
	level.getLayer()->addChild( _representation, zIndex );
}

}