#include "VerticalFollow.hpp"

namespace ThirdParty
{

namespace Extensions
{

VerticalFollow *
VerticalFollow::create(cocos2d::Node * followedNode, std::pair<float, float> constraint, const cocos2d::Rect & rect)
{
	VerticalFollow * follow = new (std::nothrow) VerticalFollow();
    if (follow && follow->initWithTarget(followedNode, constraint, rect))
    {
        follow->autorelease();
        return follow;
    }
    CC_SAFE_DELETE(follow);
    return nullptr;
}

bool
VerticalFollow::initWithTarget(cocos2d::Node * followedNode, std::pair<float, float> constraint, const cocos2d::Rect & rect)
{
	_constraint = constraint;
	return cocos2d::Follow::initWithTarget(followedNode, rect);
}

void
VerticalFollow::step(float dt)
{
	CC_UNUSED_PARAM(dt);

    if(_boundarySet)
    {
        if(_boundaryFullyCovered)
        {
            return;
        }

		if(_followedNode->getPosition().y < _constraint.first || _followedNode->getPosition().y > _constraint.second)
			return;

		float value = cocos2d::clampf(_halfScreenSize.y - _followedNode->getPosition().y, _bottomBoundary, _topBoundary);
		float delta = _target->getPositionY() - value;
        _target->setPositionY(value);
		for(Interfaces::IViewPort * view : _fixedViews)
			view->update(cocos2d::Vec2(0.0f, delta));
    }
    else
    {
		float posit = _followedNode->getPosition().y;

		if(_followedNode->getPosition().y < _constraint.first || _followedNode->getPosition().y > _constraint.second)
			return;

		float value = _halfScreenSize.y - _followedNode->getPosition().y;
		float delta = _target->getPositionY() - value;
        _target->setPositionY(value);
		for(Interfaces::IViewPort * view : _fixedViews)
			view->update(cocos2d::Vec2(0.0f, delta));
    }
}

}

}