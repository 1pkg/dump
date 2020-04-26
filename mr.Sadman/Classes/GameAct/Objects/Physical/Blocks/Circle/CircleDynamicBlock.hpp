#ifndef __GAME_ACT_PHYSICAL_CIRCLE_DYNAMIC_BLOCK_HPP__
#define __GAME_ACT_PHYSICAL_CIRCLE_DYNAMIC_BLOCK_HPP__

#include "CircleStaticBlock.hpp"

namespace GameAct
{

namespace Physical
{

class CircleDynamicBlock
	: public CircleStaticBlock
{
public:

	void initialize() override;
};

}

}

#endif
