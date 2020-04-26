#ifndef __GAME_ACT_PHYSICAL_SHARED_SPIKED_BALL_HPP__
#define __GAME_ACT_PHYSICAL_SHARED_SPIKED_BALL_HPP__

#include "GameAct/Objects/Object.hpp"

namespace GameAct
{

namespace Physical
{

class SpikedBall
	: public Object
{
public:

	void initialize() override;

	std::string getResourcesName() const override;
};

}

}

#endif
