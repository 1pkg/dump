#include "GameAct/Act.hpp"
#include "Kit.hpp"
#include "Segment.hpp"
#include "Line.hpp"
#include "GameAct/Colors/Pallete.hpp"
#include "GameAct/Objects/Registry.hpp"
#include "GameAct/Objects/Character.hpp"
#include "Resources/Constants.hpp"

namespace GameAct
{

namespace Contours
{

bool
Kit::handle(const Interfaces::IObserverable * obsable)
{
	const Segment * segment = dynamic_cast<const Segment *>(obsable);
	if(!segment)
		return false;

	_segments.erase(std::remove_if(
		_segments.begin(),
		_segments.end(),
		[segment](const std::unique_ptr<Segment> & segmentArg)
		{
			return segmentArg.get() == segment;
		}
	));

	return true;
}

Kit::Kit(cocos2d::Layer * layer)
	: _expert(this), _layer(layer), _listener(cocos2d::EventListenerTouchOneByOne::create()), _currentTouch(nullptr)
{
	/*			OnTouchBegan			*/
	_listener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		if(_currentTouch)
			return false;
		else
			_currentTouch = touch;

		_current.reset(
			new Segment(
				this,
				Act::getInstance().getPallete()->getCurrentDye()
			)
		);
		_p1 = touch->getLocation() - _layer->getPosition();
		_temp = _p1;

		_layer->schedule(std::bind(&Kit::update, this), "SceneMoveScheduler");

		return true;
	};
				/**/

	/*			OnTouchMoved			*/
	_listener->onTouchMoved = [this](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		if(_currentTouch != touch)
			return;

		handleLine(touch->getLocation() - _layer->getPosition());
		_temp = touch->getLocation() - _layer->getPosition();
	};
				/**/

	/*			OnTouchEnded			*/
	_listener->onTouchEnded = [this](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		if(_currentTouch != touch)
			return;
		else
			_currentTouch = nullptr;

		_current->blank();
		_segments.push_back(std::move(_current));

		_layer->unschedule("SceneMoveScheduler");
	};
				/**/

	_layer->getEventDispatcher()->addEventListenerWithFixedPriority(_listener, 2);
}

Kit::~Kit()
{
	_layer->unschedule("SceneMoveScheduler");

	_layer->getEventDispatcher()->removeEventListener(_listener);
}

Interfaces::IObjectView *
Kit::findObjectView(cocos2d::PhysicsBody * body) const
{
	for(auto & segment : _segments)
		for(auto & line : segment->_lines)
			if(line->getPhysicsBody() == body)
				return line.get();

	return nullptr;
}

bool
Kit::intersect(cocos2d::Rect rect) const
{
	for(auto & segment : _segments)
		for(auto & line : segment->_lines)
			if(line->getBoundingBox().intersectsRect(rect))
				return true;

	return false;
}

cocos2d::Layer *
Kit::getLayer() const
{
	return _layer;
}

const KitExpert &
Kit::getExpert() const
{
	return _expert;
}

void
Kit::update()
{
	_p1.x -= Resources::Constants::SCENE_SPEED;
	handleLine(_temp);
}

void
Kit::handleLine(cocos2d::Vec2 point)
{
	_p2 = point;
	std::unique_ptr<Line> line(new Line(_p1, _p2));
	
	cocos2d::Rect lineBoundingBox = line->getBoundingBox();
	if(Act::getInstance().getCharacter()->getBoundingBox().intersectsRect(lineBoundingBox) || Act::getInstance().getRegistry()->intersect(lineBoundingBox))
		return;

	if(_current->attachLine(line))
		_p1 = _p2;
}

}

}