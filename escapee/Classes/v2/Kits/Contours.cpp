#include "Contours.hpp"

namespace Kits
{

Contours::Contours(cocos2d::Layer * layer)
	: _dye(Dye(cocos2d::Color4F::GREEN, 30000.0f)), _layer(layer), _listener(cocos2d::EventListenerTouchOneByOne::create()), _touch(nullptr)
{
	_listener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		if(_touch)
			return false;
			
		_touch = touch;
		_p2 = _p1 = touch->getLocation() - _layer->getPosition();
		_segment.reset(new Segment());
		return true;
	};

	_listener->onTouchMoved = [this](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		if(_touch != touch)
			return;

		_p2 = touch->getLocation() - _layer->getPosition();
		track();
	};


	_listener->onTouchEnded = [this](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		if(_touch != touch)
			return;

		_touch = nullptr;
		_segments.insert(std::move(_segment));
	};
	_layer->getEventDispatcher()->addEventListenerWithFixedPriority(_listener, 2);
}

void
Contours::update(float dt)
{
	cocos2d::Vec2 delta(-10.0, 0.0);
	for (auto it = _segments.begin(); it != _segments.end(); ++it)
		if (it->get()->empty())
			_segments.erase(it);
		else
			for (auto nestedIt = it->get()->begin(); nestedIt != it->get()->end(); ++nestedIt)
				nestedIt->get()->update(delta, dt);

	if (_segment)
		for (auto it = _segment->begin(); it != _segment->end(); ++it)
			it->get()->update(delta, dt);

	if (_touch)
	{
		_p1 += delta;
		track();
	}
}

void
Contours::track()
{
	_line.reset(new Line(_p1, _p2, _dye.color(), _segment.get()));
	_line->render()->attach(_layer);
	if (_dye.get() < _line->length())
		_touch = nullptr;
	if (!_line->hollow())
	{
		_dye.update(-_line->length());
		_p1 = _p2;
	}
	_segment->attach(std::move(_line));
}

}