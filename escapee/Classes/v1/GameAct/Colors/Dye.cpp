#include "Pallete.hpp"
#include "Dye.hpp"
#include "Resources/Constants.hpp"

namespace GameAct
{

namespace Colors
{

void
Dye::nortify() const
{
	for(Interfaces::IObserver * obs : _observers)
		obs->handle(this);
}

Dye::Dye()
	: _color(cocos2d::Color4F::BLACK), _amount(0.0f)
{
}

Dye::Dye(cocos2d::Color4F color, float amount)
	: _color(color), _amount(amount)
{
}

cocos2d::Color4F
Dye::getColor() const
{
	return _color;
}
	
float
Dye::getAmount() const
{
	return _amount;
}

void
Dye::setAmount(float amount)
{
	_amount = amount;
	nortify();
}

void
Dye::updateAmount(float amount)
{
	_amount += amount;
	nortify();
}

bool
Dye::empty() const
{
	return _amount == 0.0f;
}

bool
Dye::equalColor(cocos2d::Color4F first, cocos2d::Color4F last)
{
	return first.r == last.r && first.g == last.g && first.b == last.b && first.a == last.a;
}

}

}