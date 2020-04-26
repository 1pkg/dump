#ifndef __GAME_ACT_CONTOURS_SEGMENT_HPP__
#define __GAME_ACT_CONTOURS_SEGMENT_HPP__

#include "Interfaces/INoncopyable.hpp"
#include "Interfaces/IObserverable.hpp"
#include "Interfaces/IObserver.hpp"

#include <cocos2d.h>

namespace GameAct
{

namespace Colors
{

class Dye;

}

namespace Contours
{

class Kit;
class Line;

class KitExpert;

class Segment : Interfaces::INoncopyable, public Interfaces::IObserverable, public Interfaces::IObserver
{
public:

	void nortify() const override;

public:

	bool handle(const Interfaces::IObserverable * obsable) override;

public:

	Segment(Kit * kit, Colors::Dye & dye);

	Kit * getParentKit() const;

	bool hasLine(Line * line) const;

	bool attachLine(std::unique_ptr<Line> & line);
	void blank();

	cocos2d::Color4F getColor() const;

	friend Kit;
	friend KitExpert;

private:

	Kit * _kit;

	Colors::Dye & _dye;

	bool _isBlanked;
	std::unique_ptr<Line> _current;
	std::vector<std::unique_ptr<Line>> _lines;
};

}

}

#endif