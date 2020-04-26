#ifndef __GAME_ACT_PHYSICAL_GEAR_HPP__
#define __GAME_ACT_PHYSICAL_GEAR_HPP__

#include "GameAct/Objects/Object.hpp"

namespace GameAct
{

namespace Physical
{

class Gear
	: public Object
{
public:

	std::string getName() const override;

	void setAdditionalParam( std::string additionalParam ) override;

	void runAction( const std::string & action ) override;

private:

	float _time;
};

}

}

#endif
