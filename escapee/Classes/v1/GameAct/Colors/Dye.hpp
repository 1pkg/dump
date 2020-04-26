#ifndef __GAME_ACT_COLORS_DYE_HPP__
#define __GAME_ACT_COLORS_DYE_HPP__

#include "Interfaces/IObserverable.hpp"
#include "Interfaces/IObserver.hpp"

#include <cocos2d.h>

namespace GameAct
{

namespace Colors
{

class Dye : public Interfaces::IObserverable
{
public:

	void nortify() const override;

public:

	Dye();
	Dye(cocos2d::Color4F color, float amount);

	cocos2d::Color4F getColor() const;
	
	float getAmount() const;
	void setAmount(float amount);
	void updateAmount(float amount);

	bool empty() const;

public:

	static bool equalColor(cocos2d::Color4F first, cocos2d::Color4F last);

private:
	
	cocos2d::Color4F _color;
	float _amount;
};

}

}

#endif