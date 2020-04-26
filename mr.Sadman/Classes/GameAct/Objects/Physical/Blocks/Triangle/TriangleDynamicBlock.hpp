#ifndef __GAME_ACT_PHYSICAL_TRIANGLE_DYNAMIC_BLOCK_HPP__
#define __GAME_ACT_PHYSICAL_TRIANGLE_DYNAMIC_BLOCK_HPP__

#include "TriangleStaticBlock.hpp"

namespace GameAct
{

namespace Physical
{

class TriangleDynamicBlock
	: public TriangleStaticBlock
{
public:

	void initialize() override;
};

}

}

#endif
