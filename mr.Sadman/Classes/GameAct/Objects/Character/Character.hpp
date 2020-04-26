#ifndef __GAME_ACT_CHARACTER_HPP__
#define __GAME_ACT_CHARACTER_HPP__

#include "GameAct/Objects/SubTypes/CompositeLongObject.hpp"

#include "Hip.hpp"
#include "Head.hpp"
#include "Arm.hpp"
#include "Hand.hpp"
#include "Leg.hpp"
#include "Foot.hpp"

namespace GameAct
{

class Character
	: public CompositeLongObject
{
public:

	void initialize() override;

	std::string getResourcesName() const override;

	void setSize( cocos2d::Size size ) override;

	void runAction( const std::string & action ) override;	

	std::function<void()> func;
};

}

#endif
