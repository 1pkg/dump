#include "Gear.hpp"

namespace Objects
{

namespace Tech
{

void
Gear::initialize()
{
	DecorateObject::initialize();

	_sprite->runAction( cocos2d::RepeatForever::create( cocos2d::RotateBy::create( 1.0f, 360.0f ) ) );
}

std::string
Gear::getName() const
{
	return "Gear";
}

}

}