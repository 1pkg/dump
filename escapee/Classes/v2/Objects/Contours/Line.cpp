#include "Line.hpp"
#include "Segment.hpp"

namespace Objects
{

namespace Contours
{

Line::Line(cocos2d::Vec2 p1, cocos2d::Vec2 p2, cocos2d::Color4F color, Segment * parent)
	: _parent(parent), _p1(p1), _p2(p2), _color(color), _view(nullptr)
{
	_hollow = length() <= 30.0f;
}

cocos2d::Vec2
Line::firstPoint() const
{
	return _p1;
}

cocos2d::Vec2
Line::lastPoint() const
{
	return _p2;
}

float
Line::length() const
{
	return sqrt(pow(_p1.x - _p2.x, 2.0f) + pow(_p1.y - _p2.y, 2.0f));
}

float
Line::koeficient() const
{
	return (_p1.y - _p2.y) / (_p2.x - _p1.x);
}

Segment *
Line::parent() const
{
	return _parent;
}

bool
Line::hollow() const
{
	return _hollow;
}

supps::View *
Line::render()
{
	_view.reset(new Views::Contours::Line(_p1, _p2, _color, _hollow));
	return _view.get();	
}

void
Line::update(cocos2d::Vec2 delta, float dt)
{
	_p1 += delta, _p2 += delta;
	if (_view)
		_view->update(delta, dt);
}

}

}