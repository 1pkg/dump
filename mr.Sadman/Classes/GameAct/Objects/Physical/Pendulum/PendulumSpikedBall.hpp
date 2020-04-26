#ifndef __GAME_ACT_PHYSICAL_PENDULUM_SPIKED_BALL_HPP__
#define __GAME_ACT_PHYSICAL_PENDULUM_SPIKED_BALL_HPP__

#include "Pendulum.hpp"

namespace GameAct
{

namespace Physical
{

class PendulumSpikedBall
	: public Pendulum
{
public:

	std::string getResourcesName() const override;
};

}

}

#endif
