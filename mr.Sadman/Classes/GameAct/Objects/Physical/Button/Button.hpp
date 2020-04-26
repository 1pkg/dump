#ifndef __GAME_ACT_PHYSICAL_BUTTON_HPP__
#define __GAME_ACT_PHYSICAL_BUTTON_HPP__

#include "GameAct/Objects/Object.hpp"

namespace GameAct
{

namespace Physical
{

class Button
	: public Object
{
public:

	void initialize() override;

	std::string getResourcesName() const override;

	void setRotation( float angle ) override;

	void runAction( const std::string & action ) override;

protected:

	float _angle;

};

}

}

#endif
