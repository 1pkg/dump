#ifndef __GAME_ACT_PHYSICAL_SHARED_PIVOT_HPP__
#define __GAME_ACT_PHYSICAL_SHARED_PIVOT_HPP__

#include "GameAct/Objects/Object.hpp"

namespace GameAct
{

namespace Physical
{

class Pivot
	: public Object
{
public:

	void initialize() override;

	std::string getResourcesName() const override;

	void setAdditionalParam( std::string additionalParam ) override;
	void setRotation( float angle ) override;

	void runAction( const std::string & action ) override;

private:

	cocos2d::Vec2 rotatePoint( cocos2d::Vec2 point, cocos2d::Vec2 center, float angle ) const;

	float _angle;

	float _time;
};

}

}

#endif
