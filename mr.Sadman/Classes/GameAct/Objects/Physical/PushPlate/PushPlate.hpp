#ifndef __GAME_ACT_PHYSICAL_PUSH_PLATE_HPP__
#define __GAME_ACT_PHYSICAL_PUSH_PLATE_HPP__

#include "GameAct/Objects/Physical/Button/Button.hpp"

namespace GameAct
{

namespace Physical
{

class PushPlate
	: public Button
{
public:

	void setRotation( float angle ) override;

	void runAction( const std::string & action ) override;
};

}

}

#endif
