#include "Kit.hpp"
#include "Segment.hpp"
#include "Line.hpp"
#include "Resources/Constants.hpp"

namespace GameAct
{

namespace Contours
{

Interfaces::IObject::Type
Line::getType() const
{
	return Interfaces::IObject::Type::Line;
}

bool
Line::contact(IObject * object)
{
	return object->interact(this);
}

bool
Line::interact(GameAct::Objects::Character * character)
{
	return true;
}

cocos2d::Rect
Line::getBoundingBox() const
{
	float minX = -Resources::Constants::DRAW_LINE_WIDTH, maxX = Resources::Constants::DRAW_LINE_WIDTH;
	if(getFirstPoint().x < getLastPoint().x)
	{
		minX += getFirstPoint().x;
		maxX += getLastPoint().x;
	}
	else
	{
		minX += getLastPoint().x;
		maxX += getFirstPoint().x;
	}

	float minY = -Resources::Constants::DRAW_LINE_WIDTH, maxY = Resources::Constants::DRAW_LINE_WIDTH;
	if(getFirstPoint().y < getLastPoint().y)
	{
		minY += getFirstPoint().y;
		maxY += getLastPoint().y;
	}
	else
	{
		minY += getLastPoint().y;
		maxY += getFirstPoint().y;
	}

	return cocos2d::Rect(minX, minY, maxX - minX, maxY - minY);
}

cocos2d::PhysicsBody *
Line::getPhysicsBody() const
{
	return _node->getPhysicsBody();
}

void
Line::nortify() const
{
	for(Interfaces::IObserver * obs : _observers)
		if(obs->handle(this))
			break;
}

Line::Line(cocos2d::Vec2 p1, cocos2d::Vec2 p2)
	: _segment(nullptr), _p1(p1), _p2(p2), _node(cocos2d::DrawNode::create())
{
}

Line::~Line()
{
	if(_segment)
	{
		_node->getPhysicsBody()->removeFromWorld();
		_node->removeComponent(_node->getPhysicsBody());
		
		_segment->getParentKit()->getLayer()->stopAction(_updateActionRelease);
	}

	_node->removeFromParentAndCleanup(true);
}

cocos2d::Vec2
Line::getFirstPoint() const
{
	return _p1 + _node->getPosition();
}

cocos2d::Vec2
Line::getLastPoint() const
{
	return _p2 + _node->getPosition();
}

float
Line::getLenth() const
{
	return sqrt(pow(getFirstPoint().x - getLastPoint().x, 2.0f) + pow(getFirstPoint().y - getLastPoint().y, 2.0f));
}

float
Line::getKoef() const
{
	return (getLastPoint().y - getFirstPoint().y) / (getLastPoint().x - getFirstPoint().x);
}

Segment *
Line::getParentSegment() const
{
	return _segment;
}

void
Line::attachToSegment(Segment * segment)
{
	if(_segment)
		return;

	_segment = segment;
	_segment->getParentKit()->getLayer()->addChild(_node);
	
	_node->drawLine(getFirstPoint(), getLastPoint(), _segment->getColor());

	_node->runAction(
		cocos2d::RepeatForever::create(
			cocos2d::MoveBy::create(
				1.0f, cocos2d::Vec2(-30.0f, 0.0f)
			)
		)
	);

	/*			ReleaseAction			*/
	_updateActionRelease = cocos2d::Sequence::create(
		cocos2d::DelayTime::create(Resources::Constants::LINE_REALESE_TIME),
		cocos2d::CallFunc::create(std::bind(&Line::nortify, this)),
		nullptr
	);
	_segment->getParentKit()->getLayer()->runAction(_updateActionRelease);
				/**/

	/*			PhysicsSetup			*/
	_node->setPhysicsBody(cocos2d::PhysicsBody::createEdgeSegment(getFirstPoint(), getLastPoint()));
	_node->getPhysicsBody()->setDynamic(false);
	_node->getPhysicsBody()->setCategoryBitmask(Resources::Constants::LINE_MASK);
	_node->getPhysicsBody()->setCollisionBitmask(Resources::Constants::CHARACTER_MASK);
	_node->getPhysicsBody()->setContactTestBitmask(Resources::Constants::CHARACTER_MASK);
				/**/
}

}

}