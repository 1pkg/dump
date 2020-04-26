#ifndef __GAME_ACT_PHYSICAL_DYNAMI_SAW_HPP__
#define __GAME_ACT_PHYSICAL_DYNAMI_SAW_HPP__

#include "StaticSaw.hpp"

namespace GameAct
{

namespace Physical
{

class DynamicSaw
	: public StaticSaw
{
public:

	void initialize() override;
};

}

}

#endif
