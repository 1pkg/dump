#ifndef __TECH_EXPLOSION_HPP__
#define __TECH_EXPLOSION_HPP__

#include "Game/Objects/SubTypes/Stream.hpp"

/* FINISHED ?Particles? */

namespace Objects
{

namespace Tech
{

class Explosion : public Stream
{
public:
/* Handle event overriding*/

public:
/* Interactors overriding*/

public:
/* Object parts overriding*/

	Explosion();

	void initialize() override;

	std::string getName() const override;

	void setSize( cocos2d::Size size ) override;
};

}

}

#endif
