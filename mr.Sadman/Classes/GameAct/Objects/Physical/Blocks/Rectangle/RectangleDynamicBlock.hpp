#ifndef __GAME_ACT_PHYSICAL_DYNAMIC_RECTANGLE_DYNAMIC_BLOCK_HPP__
#define __GAME_ACT_PHYSICAL_DYNAMIC_RECTANGLE_DYNAMIC_BLOCK_HPP__

#include "RectangleStaticBlock.hpp"

namespace GameAct
{

namespace Physical
{

class RectangleDynamicBlock
	: public RectangleStaticBlock
{
public:

	void initialize() override;

	void runAction( const std::string & action ) override;
};

}

}

#endif
