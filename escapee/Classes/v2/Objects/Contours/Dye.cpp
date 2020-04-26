#include "Dye.hpp"

namespace Objects
{

namespace Contours
{

Dye::Dye(cocos2d::Color4F color, float amount)
	: _color(color), _amount(amount)
{
}

cocos2d::Color4F
Dye::color() const
{
	return _color;
}
	
float
Dye::get() const
{
	return _amount;
}

void
Dye::update(float amount)
{
	_amount += amount;
	nortify();
}

bool
Dye::empty() const
{
	return _amount == 0.0f;
}

void
Dye::nortify()
{
	for(supps::Observer * observers : _observers)
		observers->handle(this);
}

}

}