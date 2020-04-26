#ifndef __GAME_ACT_CONTOURS_LINE_HPP__
#define __GAME_ACT_CONTOURS_LINE_HPP__

#include "Interfaces/IObjectView.hpp"
#include "Interfaces/IObserverable.hpp"
#include "Interfaces/IObserver.hpp"

#include <cocos2d.h>

namespace GameAct
{

namespace Contours
{

class Segment;

class KitExpert;

class Line :  public Interfaces::IObjectView, public Interfaces::IObserverable
{
public:

	Interfaces::IObject::Type getType() const override;

	bool contact(IObject * object) override;

	bool interact(GameAct::Objects::Character * character) override;

	cocos2d::Rect getBoundingBox() const override;
	
	cocos2d::PhysicsBody * getPhysicsBody() const override;

public:

	void nortify() const override;

public:

	Line(cocos2d::Vec2 p1, cocos2d::Vec2 p2);
	~Line();

	cocos2d::Vec2 getFirstPoint() const;
	cocos2d::Vec2 getLastPoint() const;
	float getLenth() const;
	float getKoef() const;

	Segment * getParentSegment() const;

	void attachToSegment(Segment * segment);

	friend KitExpert;

private:

	Segment * _segment;

	cocos2d::Vec2 _p1, _p2;

	cocos2d::DrawNode * _node;
	cocos2d::Action * _updateActionRelease;
};

}

}

#endif