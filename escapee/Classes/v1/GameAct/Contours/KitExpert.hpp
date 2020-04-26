#ifndef __GAME_ACT_CONTOURS_KIT_EXPERT_HPP__
#define __GAME_ACT_CONTOURS_KIT_EXPERT_HPP__

#include "Interfaces/INoncopyable.hpp"

#include <cocos2d.h>

namespace GameAct
{

namespace Contours
{

class Kit;
class Segment;
class Line;

class KitExpert : public Interfaces::INoncopyable
{
public:

	KitExpert(Kit * path);

	Segment * getSegment(cocos2d::PhysicsBody * body) const;

	bool intersect(cocos2d::Rect rect) const;

	bool hasSegmentUnder(cocos2d::Vec2 point) const;
	bool hasSegmentBellow(cocos2d::Vec2 point) const;

	bool isEndOfSegment(cocos2d::Vec2 point, float delta) const;

	cocos2d::Color4F getSegmentColor(cocos2d::Vec2 point) const;

private:

	std::vector<Line *> findLines(cocos2d::Vec2 point, bool orientation) const;
	std::vector<Segment *> findSegments(cocos2d::Vec2 point) const;

	Kit * _kit;
};

}

}

#endif