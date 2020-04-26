#ifndef __GAME_ACT_PHYSICAL_TRAMPOLINE_HPP__
#define __GAME_ACT_PHYSICAL_TRAMPOLINE_HPP__

#include "GameAct/Objects/Object.hpp"

namespace GameAct
{

namespace Physical
{

class Trampoline
	: public Object
{
public:

	void initialize() override;

	std::string getResourcesName() const override;

	void runAction( const std::string & action ) override;
};

}

}

#endif
