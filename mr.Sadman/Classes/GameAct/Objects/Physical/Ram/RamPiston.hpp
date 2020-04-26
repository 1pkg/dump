#ifndef __GAME_ACT_PHYSICAL_RAM_PISTON_HPP__
#define __GAME_ACT_PHYSICAL_RAM_PISTON_HPP__

#include "GameAct/Objects/Object.hpp"

namespace GameAct
{

namespace Physical
{

class RamPiston
	: public Object
{
public:

	void initialize() override;

	std::string getResourcesName() const override;

	void setPosition( cocos2d::Vec2 position ) override;
	void setAdditionalParam( std::string additionalParam ) override;
	void setRotation( float angle ) override;

	void runAction( const std::string & action ) override;

private:

	cocos2d::Vec2 _position;

	float _angle;

	bool _deadly;

	float _time;
	float _delay;
};

}

}

#endif
