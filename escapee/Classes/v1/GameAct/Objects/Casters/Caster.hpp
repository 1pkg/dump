#ifndef __GAME_ACT_OBECTS_SHELLS_CASTERS_CASTER_HPP__
#define __GAME_ACT_OBECTS_SHELLS_CASTERS_CASTER_HPP__

#include "Interfaces/IObjectView.hpp"

#include <cocos2d.h>

namespace GameAct
{

namespace Objects
{

namespace Casters
{

class Caster : public Interfaces::IObjectView
{
public:

	Interfaces::IObject::Type getType() const override;

	bool contact(IObject * object) override;

	cocos2d::Rect getBoundingBox() const override;
	
	cocos2d::PhysicsBody * getPhysicsBody() const override;

public:

	Caster(cocos2d::Layer * layer);
	~Caster();

private:

	void cast();

	cocos2d::Sprite * _sprite;
	cocos2d::Layer * _layer;
};

}

}

}

#endif