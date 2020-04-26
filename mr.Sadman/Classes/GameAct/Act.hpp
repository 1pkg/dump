#ifndef __GAME_ACT_HPP__
#define __GAME_ACT_HPP__

#include "Resources/Forward.hpp"

#include "ThirdParty/noncopyable.hpp"

#include <cocos2d.h>

#include <memory>

namespace GameAct
{

class Level;

class ObjectsFactory;

class Act
	: public ThirdParty::noncopyable
{
public:

	static Act * create( Resources::Lab lab, int levelIndex, cocos2d::Layer * layer, cocos2d::PhysicsWorld * physicWorld );

	~Act();

	void initialize();

	Level * getLevel() const;
	ObjectsFactory * getObjectsFactory() const;

private:

	std::unique_ptr< Level > _level;
	std::unique_ptr< ObjectsFactory > _objectsFactory;
};

}

#endif