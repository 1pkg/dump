#include "Act.hpp"
#include "GameAct/Levels/Level.hpp"
#include "GameAct/Objects/Object.hpp"
#include "GameAct/Objects/Factories/ObjectsFactory.hpp"
#include "Resources/Cache/Cache.hpp"

namespace GameAct
{

Act *
Act::create( Resources::Lab lab, int levelIndex, cocos2d::Layer * layer, cocos2d::PhysicsWorld * physicWorld )
{
	Act * act = new Act();
	Resources::Cache::getInstance().restart( lab, levelIndex );
	act->_objectsFactory.reset( ObjectsFactory::create( lab ) );
	act->_level.reset( Level::create( layer, physicWorld ) );
	return act;
}

Act::~Act() // for uniq_ptr
{
}

void
Act::initialize()
{

	_level->updateChunks();
	_level->updateChunks();
	_level->updateChunks();
}

Level *
Act::getLevel() const
{
	return _level.get();
}

ObjectsFactory *
Act::getObjectsFactory() const
{
	return _objectsFactory.get();
}

}