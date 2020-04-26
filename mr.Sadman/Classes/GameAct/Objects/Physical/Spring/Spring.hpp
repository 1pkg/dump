#ifndef __GAME_ACT_PHYSICAL_SPRING_HPP__
#define __GAME_ACT_PHYSICAL_SPRING_HPP__

#include "GameAct/Objects/Object.hpp"

namespace GameAct
{

namespace Physical
{

class Spring
	: public Object
{
public:

	void initialize() override;

	std::string getResourcesName() const override;

	void setRotation( float angle ) override;

	void runAction( const std::string & action ) override;

private:

	float _angle;
};

}

}

#endif
