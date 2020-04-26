#ifndef __GAME_ACT_OBECTS_SHELLS_GREEN_ARROW_HPP__
#define __GAME_ACT_OBECTS_SHELLS_GREEN_ARROW_HPP__

#include "Interfaces/IObjectView.hpp"

#include <cocos2d.h>

namespace GameAct
{

namespace Objects
{

namespace Shells
{

class GreenArrow : public Interfaces::IObjectView
{
public:

	Interfaces::IObject::Type getType() const override;

	bool contact(IObject * object) override;

	cocos2d::Rect getBoundingBox() const override;
	
	cocos2d::PhysicsBody * getPhysicsBody() const override;

public:

	GreenArrow(cocos2d::Layer * layer, cocos2d::Vec2 posit);
	~GreenArrow();

private:

	cocos2d::Sprite * _sprite;
};

}

}

}

#endif