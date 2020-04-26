#ifndef __GAME_ACT_OBECTS_REQUIRES_SPIKES_HPP__
#define __GAME_ACT_OBECTS_REQUIRES_SPIKES_HPP__

#include "Interfaces/IObjectView.hpp"

#include <cocos2d.h>

namespace GameAct
{

namespace Objects
{

namespace Requires
{

class Spikes : public Interfaces::IObjectView
{
public:

	Interfaces::IObject::Type getType() const override;

	bool contact(IObject * object) override;

	bool interact(GameAct::Objects::Character * character) override;

	cocos2d::Rect getBoundingBox() const override;
	
	cocos2d::PhysicsBody * getPhysicsBody() const override;

public:

	Spikes(cocos2d::Layer * layer);
	~Spikes();

private:

	void update();
	void fillUp();

	cocos2d::DrawNode * _node;
	cocos2d::ParticleSystemQuad * _particle;

private:

	struct Triangle
	{
		cocos2d::Vec2 p1, p2, p3;
	};
	std::vector<Triangle> _triangles;
};

}

}

}

#endif