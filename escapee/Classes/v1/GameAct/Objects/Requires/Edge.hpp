#ifndef __GAME_ACT_OBECTS_REQUIRES_EDGE_HPP__
#define __GAME_ACT_OBECTS_REQUIRES_EDGE_HPP__

#include "Interfaces/IObjectView.hpp"

#include <cocos2d.h>

namespace GameAct
{

namespace Objects
{

namespace Requires
{

class Edge : public Interfaces::IObjectView
{
public:

	Interfaces::IObject::Type getType() const override;

	bool contact(IObject * object) override;

	bool interact(GameAct::Objects::Character * character) override;

	cocos2d::Rect getBoundingBox() const override;
	
	cocos2d::PhysicsBody * getPhysicsBody() const override;

public:

	Edge(cocos2d::Layer * layer);
	~Edge();

private:

	cocos2d::ParticleSystemQuad * _particle;
};

}

}

}

#endif