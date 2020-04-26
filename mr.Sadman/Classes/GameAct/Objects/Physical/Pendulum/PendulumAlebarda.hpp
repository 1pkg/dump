#ifndef __GAME_ACT_PHYSICAL_PENDULUM_ALEBARDA_HPP__
#define __GAME_ACT_PHYSICAL_PENDULUM_ALEBARDA_HPP__

#include "Pendulum.hpp"

namespace GameAct
{

namespace Physical
{

class PendulumAlebarda
	: public Pendulum
{
public:

	std::string getResourcesName() const override;
};

}

}

#endif
