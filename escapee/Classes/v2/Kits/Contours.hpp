#ifndef __KITS_CONTOURS_HPP__
#define __KITS_CONTOURS_HPP__

#include "Environment/fwd.hpp"
#include "Objects/Contours/Segment.hpp"
#include "Objects/Contours/Line.hpp"
#include "Objects/Contours/Dye.hpp"
#include <cocos2d.h>

namespace Kits
{

using namespace Objects::Contours;
class Contours : public supps::Kit
{
public:

	Contours(cocos2d::Layer * layer);
	void update(float dt) override;

private:

	void track();

	cocos2d::Vec2 _p1, _p2;
	std::unique_ptr<Line> _line;
	std::unique_ptr<Segment> _segment;
	std::unordered_set<std::unique_ptr<Segment>> _segments;
	Dye _dye;

	cocos2d::EventListenerTouchOneByOne * _listener;
	cocos2d::Touch * _touch;
	cocos2d::Layer * _layer;
};

}

#endif