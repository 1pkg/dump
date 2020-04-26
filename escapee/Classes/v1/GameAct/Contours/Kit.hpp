#ifndef __GAME_ACT_CONTOURS_KIT_HPP__
#define __GAME_ACT_CONTOURS_KIT_HPP__

#include "Interfaces/IObjectView.hpp"
#include "Interfaces/IObserverable.hpp"
#include "Interfaces/IObserver.hpp"
#include "KitExpert.hpp"

#include <cocos2d.h>

namespace GameAct
{

namespace Contours
{

class Segment;

class Kit : public Interfaces::INoncopyable, public Interfaces::IObserver
{
public:

	bool handle(const Interfaces::IObserverable * obsable) override;

public:

	Kit(cocos2d::Layer * layer);
	~Kit();

	Interfaces::IObjectView * findObjectView(cocos2d::PhysicsBody * body) const;

	bool intersect(cocos2d::Rect rect) const;

	cocos2d::Layer * getLayer() const;

	const KitExpert & getExpert() const;

	friend KitExpert;

private:

	void update();
	void handleLine(cocos2d::Vec2 point);

	KitExpert _expert;

	cocos2d::Vec2 _p1, _p2, _temp;
	std::unique_ptr<Segment> _current;
	std::vector<std::unique_ptr<Segment>> _segments;
	
	cocos2d::Layer * _layer;
	cocos2d::EventListenerTouchOneByOne * _listener;
	cocos2d::Touch * _currentTouch;
};

}

}

#endif