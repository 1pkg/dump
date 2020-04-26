#ifndef __OBJECTS_CONTOURS_LINE_HPP__
#define __OBJECTS_CONTOURS_LINE_HPP__

#include "Environment/fwd.hpp"
#include "Views/Contours/Line.hpp"
#include <cocos2d.h>

namespace Objects
{

namespace Contours
{

class Segment;
class Line : public supps::Object
{
public:

	Line(cocos2d::Vec2 p1, cocos2d::Vec2 p2, cocos2d::Color4F color, Segment * parent);
	cocos2d::Vec2 firstPoint() const;
	cocos2d::Vec2 lastPoint() const;
	float length() const;
	float koeficient() const;
	Segment * parent() const;
	bool hollow() const;

	supps::View * render() override;
	void update(cocos2d::Vec2 delta, float dt);

private:

	cocos2d::Vec2 _p1, _p2;
	cocos2d::Color4F _color;
	Segment * _parent;
	bool _hollow;
	std::unique_ptr<Views::Contours::Line> _view;
};

}

}

#endif