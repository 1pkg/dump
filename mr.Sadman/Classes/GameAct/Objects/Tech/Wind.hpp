#ifndef __TECH_WIND_HPP__
#define __TECH_WIND_HPP__

#include "GameAct/Objects/SubTypes/Stream.hpp"

/* FINISHED ?Particles? */

namespace GameAct
{

namespace Tech
{

class Wind
	: public Stream
{
public:

	void initialize() override;

	std::string getName() const override;

	void setSize( cocos2d::Size size ) override;
};

}

}

#endif
