#include "KitExpert.hpp"
#include "Kit.hpp"
#include "Segment.hpp"
#include "Line.hpp"

#include <algorithm>

namespace GameAct
{

namespace Contours
{

KitExpert::KitExpert(Kit * kit)
	: _kit(kit)
{
}

Segment *
KitExpert::getSegment(cocos2d::PhysicsBody * body) const
{

	return nullptr;
}

bool
KitExpert::intersect(cocos2d::Rect rect) const
{

	return false;
}

bool
KitExpert::hasSegmentUnder(cocos2d::Vec2 point) const
{
	auto lines = findLines(point, false);
	return !lines.empty();
}

bool
KitExpert::hasSegmentBellow(cocos2d::Vec2 point) const
{
	auto lines = findLines(point, true);
	return !lines.empty();
}

bool
KitExpert::isEndOfSegment(cocos2d::Vec2 point, float delta) const
{
	auto lines = findLines(point, false);
	if(lines.empty())
		return false;

	cocos2d::Vec2 min = cocos2d::Vec2(point.x - delta, point.y);
	cocos2d::Vec2 max = cocos2d::Vec2(point.x + delta, point.y);

	return false;//!lines.front()->getParentSegment()->getBoundingBox().containsPoint(max);
}

cocos2d::Color4F
KitExpert::getSegmentColor(cocos2d::Vec2 point) const
{
	auto lines = findLines(point, false);
	if(lines.empty())
		return cocos2d::Color4F::BLACK;

	return lines.front()->getParentSegment()->getColor();
}

std::vector<Line *>
KitExpert::findLines(cocos2d::Vec2 point, bool orientation) const
{
	std::vector<std::pair<Line *, float>> lines;
	auto segments = findSegments(point);

	for(auto segment : segments)
		for(auto & line : segment->_lines)
		{
			float minX, maxX;
			if(line->getFirstPoint().x < line->getLastPoint().x)
			{
				minX = line->getFirstPoint().x;
				maxX = line->getLastPoint().x;
			}
			else
			{
				minX = line->getLastPoint().x;
				maxX = line->getFirstPoint().x;
			}

			if(point.x >= minX && point.x <= maxX)
			{
				float koef = (line->getLastPoint().y - line->getFirstPoint().y) / (line->getLastPoint().x - line->getFirstPoint().x);
				float y = line->getLastPoint().y - ((point.x - line->getFirstPoint().x) * koef);
				if(orientation)
				{
					if(point.y < y)
						lines.push_back(std::pair<Line *, float>{line.get(), point.y - y});
				}
				else
				{
					if(point.y > y)
						lines.push_back(std::pair<Line *, float>{line.get(), y - point.y});
				}
			}
		}

	std::sort(
		lines.begin(),
		lines.end(),
		[](std::pair<Line *, float> first, std::pair<Line *, float> last)
		{
			return first.second < last.second;
		}
	);

	std::vector<Line *> linesRes;
	for(auto pair : lines)
		linesRes.push_back(pair.first);

	return linesRes;
}

std::vector<Segment *>
KitExpert::findSegments(cocos2d::Vec2 point) const
{
	std::vector<Segment *> segments;
	/*for(auto & segment : _kit->_segments)
		if(segment->getBoundingBox().containsPoint(point))
			segments.push_back(segment.get());*/

	return segments;
}

}

}