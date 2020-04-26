#ifndef __GAME_ACT_SHARED_WIND_HPP__
#define __GAME_ACT_SHARED_WIND_HPP__

#include "GameAct/Objects/SubTypes/Stream.hpp"

namespace GameAct
{

namespace Shared
{

class Wind
	: public Stream
{
public:

	void initialize() override;

	std::string getResourcesName() const override;

	void setSize( cocos2d::Size size ) override;
};

}

}

#endif
