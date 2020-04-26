#include "Line.hpp"

namespace Views
{

namespace Contours
{

Line::Line(cocos2d::Vec2 p1, cocos2d::Vec2 p2, cocos2d::Color4F color, bool hollow)
	: _node(cocos2d::DrawNode::create()), _hollow(hollow)
{
	_node->drawLine(p1, p2, color);
	if (!_hollow)
	{
		_node->setPhysicsBody(cocos2d::PhysicsBody::createEdgeSegment(p1, p2));
		_node->getPhysicsBody()->setDynamic(false);
	}
}

Line::~Line()
{
	if (!_hollow)
		_node->getPhysicsBody()->removeFromWorld();
	_node->removeFromParentAndCleanup(true);
}

void
Line::attach(cocos2d::Layer * layer)
{
	layer->addChild(_node);
}

void
Line::update(cocos2d::Vec2 delta, float dt)
{
	_node->setPosition(_node->getPosition() + delta);
}

}

}