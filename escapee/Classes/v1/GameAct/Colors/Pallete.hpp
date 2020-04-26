#ifndef __GAME_CAT_COLORS_PALLETE_HPP__
#define __GAME_CAT_COLORS_PALLETE_HPP__

#include "Interfaces/INoncopyable.hpp"
#include "Interfaces/IObserverable.hpp"
#include "Interfaces/IObserver.hpp"

#include <cocos2d.h>

namespace GameAct
{

namespace Colors
{

class Dye;

class Pallete : public Interfaces::INoncopyable, public Interfaces::IObserverable, public Interfaces::IObserver
{
public:

	virtual std::vector<cocos2d::Color4F> getColors() const =0;

	virtual Dye & getDye(cocos2d::Color4F color) const =0;
	virtual Dye & getCurrentDye() const =0;
	virtual void setCurrentDye(cocos2d::Color4F color) =0;

	virtual bool hasColor(cocos2d::Color4F color) const =0;
	virtual bool empty() const =0;
};

}

}

#endif