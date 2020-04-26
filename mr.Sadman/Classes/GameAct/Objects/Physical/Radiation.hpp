#ifndef __TECH_RADIATION_HPP__
#define __TECH_RADIATION_HPP__

#include "Game/Objects/DecorateObject.hpp"

namespace Objects
{

namespace Tech
{

class Radiation : public DecorateObject
{
public:
/* Handle event overriding*/

public:
/* Interactors overriding*/

public:
/* Object parts overriding*/

	Radiation();
	~Radiation();

	void initialize() override;

	std::string getName() const override;

	void setPosition( cocos2d::Vec2 position ) override;
	void setSize( cocos2d::Size size ) override;

	void hide() override;
	void show() override;

	void attachToChunk( Levels::Chunk & chunk, int zIndex ) override;

private:

	cocos2d::ParticleSystemQuad * _particle;
};

}

}

#endif
