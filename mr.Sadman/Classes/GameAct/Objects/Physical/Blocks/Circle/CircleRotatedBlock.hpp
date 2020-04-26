#ifndef __GAME_ACT_PHYSICAL_CIRCLE_ROTATED_BLOCK_HPP__
#define __GAME_ACT_PHYSICAL_CIRCLE_ROTATED_BLOCK_HPP__

#include "CircleStaticBlock.hpp"

namespace GameAct
{

namespace Physical
{

class CircleRotatedBlock
	: public CircleStaticBlock
{
public:

	void setAdditionalParam( std::string additionalParam ) override;

	void runAction( const std::string & action ) override;

private:

	float _time;
};

}

}

#endif
