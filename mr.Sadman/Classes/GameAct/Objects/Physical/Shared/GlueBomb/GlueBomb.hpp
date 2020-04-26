#ifndef __GAME_ACT_PHYSICAL_SHARED_GLUE_BOMB_HPP__
#define __GAME_ACT_PHYSICAL_SHARED_GLUE_BOMB_HPP__

#include "GameAct/Objects/Object.hpp"

namespace GameAct
{

namespace Physical
{

class GlueBomb
	: public Object
{
public:

	void initialize() override;

	std::string getResourcesName() const override;

	void attachToChunk( Chunk & chunk, int zIndex ) override;

	void runAction( const std::string & action ) override;

private:

	int _zindex;
};

}

}

#endif
