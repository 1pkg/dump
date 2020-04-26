#ifndef __GAME_ACT_SHELL_HPP__
#define __GAME_ACT_SHELL_HPP__

#include "GameAct/Objects/Object.hpp"

namespace GameAct
{

class Shell
	: public Object
{
public:

	void initialize() override;

	std::string getName() const override;
};

}

#endif
