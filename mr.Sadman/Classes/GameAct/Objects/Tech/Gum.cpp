#include "Gum.hpp"

namespace Objects
{

namespace Tech
{

void
Gum::initialize()
{
	DecorateObject::initialize();

	auto scaleBy1 = cocos2d::ScaleBy::create( 1.0f, 0.8f, 2.0f );
	auto scaleBy2 = cocos2d::ScaleBy::create( 1.0f, 1.25f, 0.5f );
	auto sequence = cocos2d::RepeatForever::create( cocos2d::Sequence::create( scaleBy1, scaleBy2, nullptr ) );
	_sprite->runAction( sequence );
}

std::string
Gum::getName() const
{
	return "Gum";
}

}

}