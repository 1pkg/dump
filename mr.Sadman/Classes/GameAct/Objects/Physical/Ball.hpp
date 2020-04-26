#ifndef __TECH_BALL_HPP__
#define __TECH_BALL_HPP__

#include "GameAct/Objects/SubTypes/Shell.hpp"

namespace GameAct
{

namespace Tech
{

class Ball
	: public Shell
{
public:

	void initialize() override;

	std::string getName() const override;
};

}

}

#endif
