#ifndef __GAME_CAT_COLORS_RAINBOW_HPP__
#define __GAME_CAT_COLORS_RAINBOW_HPP__

#include "Pallete.hpp"
#include "Dye.hpp"

#include <array>

namespace GameAct
{

namespace Colors
{

class Rainbow : public Pallete
{
public:

	void nortify() const override;

public:

	bool handle(const Interfaces::IObserverable * obsable) override;

public:

	Rainbow();

	std::vector<cocos2d::Color4F> getColors() const override;

	Dye & getDye(cocos2d::Color4F color) const override;
	Dye & getCurrentDye() const override;
	void setCurrentDye(cocos2d::Color4F color) override;

	bool hasColor(cocos2d::Color4F color) const override;
	bool empty() const override;

private:

	unsigned int _currentIndex;
	std::array<Dye, 7> _pallete;
};

}

}

#endif