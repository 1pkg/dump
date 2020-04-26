#ifndef __VIEWS_CONTOURS_LINE_HPP__
#define __VIEWS_CONTOURS_LINE_HPP__

#include "Environment/fwd.hpp"
#include <cocos2d.h>

namespace Views
{

namespace Contours
{

class Line : public supps::View
{
public:

	Line(cocos2d::Vec2 p1, cocos2d::Vec2 p2, cocos2d::Color4F color, bool hollow);
	~Line();
	void attach(cocos2d::Layer * layer) override;
	void update(cocos2d::Vec2 delta, float dt);

private:

	bool _hollow;
	cocos2d::DrawNode * _node;
};

}

}

#endif