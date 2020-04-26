#ifndef __GAME_ACT_PHYSICAL_SHARED_ALEBARDA_HPP__
#define __GAME_ACT_PHYSICAL_SHARED_ALEBARDA_HPP__

#include "GameAct/Objects/Object.hpp"

namespace GameAct
{

namespace Physical
{

class Alebarda
	: public Object
{
public:

	void initialize() override;

	std::string getResourcesName() const override;
};

}

}

#endif
