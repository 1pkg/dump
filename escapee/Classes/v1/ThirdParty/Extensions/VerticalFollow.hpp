#ifndef __THIRD_PARTY_EXTENSIONS_VERTICAL_FOLLOW_HPP__
#define __THIRD_PARTY_EXTENSIONS_VERTICAL_FOLLOW_HPP__

#include "Interfaces/IViewPort.hpp"

#include <cocos2d.h>

#include <unordered_set>

namespace GameAct
{

namespace Objects
{

class Character;

}

}

namespace ThirdParty
{

namespace Extensions
{

class VerticalFollow : public Interfaces::INoncopyable, public cocos2d::Follow
{
public:

	static VerticalFollow * create(cocos2d::Node * followedNode, std::pair<float, float> constraint, const cocos2d::Rect & rect = cocos2d::Rect::ZERO);

	bool initWithTarget(cocos2d::Node * followedNode, std::pair<float, float> constraint, const cocos2d::Rect & rect = cocos2d::Rect::ZERO);

	void step(float dt) override;

	friend GameAct::Objects::Character;

private:

	std::pair<float, float> _constraint;

	std::unordered_set<Interfaces::IViewPort *> _fixedViews;
};

}

}

#endif