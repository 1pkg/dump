#include "Rainbow.hpp"
#include "Resources/Constants.hpp"

namespace GameAct
{

namespace Colors
{

void
Rainbow::nortify() const
{
	for(Interfaces::IObserver * obs : _observers)
		obs->handle(this);
}

bool
Rainbow::handle(const Interfaces::IObserverable * obsable)
{
	const Dye * dye = dynamic_cast<const Dye *>(obsable);
	if(!dye)
		return false;

	nortify();

	return true;
}

Rainbow::Rainbow()
	: _pallete{
		{
			Dye(cocos2d::Color4F::RED, Resources::Constants::DEFAULT_DYE_AMOUNT),
			Dye(cocos2d::Color4F::ORANGE, Resources::Constants::DEFAULT_DYE_AMOUNT),
			Dye(cocos2d::Color4F::YELLOW, Resources::Constants::DEFAULT_DYE_AMOUNT),
			Dye(cocos2d::Color4F::GREEN, Resources::Constants::DEFAULT_DYE_AMOUNT),
			Dye(cocos2d::Color4F(0.0f, 191.0f / 255.0f, 1.0f, 1.0f), Resources::Constants::DEFAULT_DYE_AMOUNT),
			Dye(cocos2d::Color4F::BLUE, Resources::Constants::DEFAULT_DYE_AMOUNT),
			Dye(cocos2d::Color4F(139.0f / 255.0f, 0.0f, 1.0f, 1.0f), Resources::Constants::DEFAULT_DYE_AMOUNT)
		}
	},
	_currentIndex(0)
{
	for(Dye & dye : _pallete)
		dye.addObserver(this);
}

std::vector<cocos2d::Color4F>
Rainbow::getColors() const
{
	std::vector<cocos2d::Color4F> result;
	for(Dye dye : _pallete)
		result.push_back(dye.getColor());

	return result;
}

Dye &
Rainbow::getDye(cocos2d::Color4F color) const
{
	return
		const_cast<Dye &>(
			*std::find_if(
				_pallete.begin(),
				_pallete.end(),
				[color](const Dye & dye)
				{
					return Dye::equalColor(dye.getColor(), color);
				}
		)
	);
}

Dye &
Rainbow::getCurrentDye() const
{
	return const_cast<Dye &>(_pallete[_currentIndex]);
}

void
Rainbow::setCurrentDye(cocos2d::Color4F color)
{
	if(!hasColor(color))
		return;

	for(unsigned int i = 0; i < _pallete.size(); ++i)
		if(Dye::equalColor(_pallete[i].getColor(), color))
		{
			_currentIndex = i;
			break;
		}
}

bool
Rainbow::hasColor(cocos2d::Color4F color) const
{
	return
		std::find_if(
			_pallete.begin(),
			_pallete.end(),
			[color](const Dye & dye)
			{
				return Dye::equalColor(dye.getColor(), color);
			}
		)
	!= _pallete.end();
}

bool
Rainbow::empty() const
{
	return
		std::count_if(
			_pallete.begin(),
			_pallete.end(),
			[](const Dye & dye)
			{
				return dye.empty();
			}
		)
	== _pallete.size();
}

}

}