#ifndef __GAME_ACT_CHARACTER_HPP__
#define __GAME_ACT_CHARACTER_HPP__

#include "GameAct/Objects/Object.hpp"

namespace GameAct
{

class Character
	: public Object
{
public:
/* Interactors overriding*/

	void interact( Edge * bg );

public:

	void initialize() override;

	std::string getName() const override;

	cocos2d::PhysicsBody * getBody() const override;

	void attachToLayer( cocos2d::Layer * layer, int zIndex );

	void runAction( const std::string & action ) override;
	void runInteraction( Object * object ) override;
};

}

#endif
