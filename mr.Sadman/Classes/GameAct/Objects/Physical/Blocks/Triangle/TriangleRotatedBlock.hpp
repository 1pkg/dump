#ifndef __GAME_ACT_PHYSICAL_TRIANGLE_ROTATED_BLOCK_HPP__
#define __GAME_ACT_PHYSICAL_TRIANGLE_ROTATED_BLOCK_HPP__

#include "TriangleStaticBlock.hpp"

namespace GameAct
{

namespace Physical
{

class TriangleRotatedBlock
	: public TriangleStaticBlock
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
