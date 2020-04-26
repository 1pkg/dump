#ifndef __GAME_ACT_PHYSICAL_BULLETS_HPP__
#define __GAME_ACT_PHYSICAL_BULLETS_HPP__

#include "GameAct/Objects/SubTypes/Stream.hpp"

namespace GameAct
{

namespace Physical
{

class Bullets
	: public Stream
{
public:

	void initialize() override;

	std::string getName() const override;

	void setSize( cocos2d::Size size ) override;
	void setRotation( float angle ) override;

private:

	float _angle;
};

}

}

#endif
