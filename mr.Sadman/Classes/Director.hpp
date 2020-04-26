#ifndef __DIRECTOR_HPP__
#define __DIRECTOR_HPP__

#include "Resources/Forward.hpp"
#include "GameAct/Forward.hpp"

#include "ThirdParty/noncopyable.hpp"

#include <cocos2d.h>

#include <memory>

class Director
	: public ThirdParty::noncopyable
{
public:

	static Director & getInstance();

	GameAct::Act * getGameAct() const;

	void restartAct( Resources::Lab lab, int levelIndex, cocos2d::Layer * layer, cocos2d::PhysicsWorld * physicWorld );
	void finishAct();

private:

	std::unique_ptr< GameAct::Act > _gameAct;
};

#endif