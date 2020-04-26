#ifndef __TECH_FLAME_HPP__
#define __TECH_FLAME_HPP__

#include "Game/Objects/StaticObject.hpp"
#include "Game/Objects//Providers/Direction.hpp"

namespace Objects
{

namespace Tech
{

class Flame : public StaticObject
{
public:
/* Handle event overriding*/

public:
/* Interactors overriding*/

public:
/* Object parts overriding*/

	Flame( Direction direction );
	~Flame();

	void initialize() override;

	std::string getName() const override;

	void setPosition( cocos2d::Vec2 position ) override;
	void setSize( cocos2d::Size size ) override;

	void hide() override;
	void show() override;

	void attachToChunk( Levels::Chunk & chunk, int zIndex ) override;

private:

	Direction _direction;
	cocos2d::ParticleSystemQuad * _particle;
};

}

}

#endif
