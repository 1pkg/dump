#include "Director.hpp"
#include "GameAct/Act.hpp"
#include "GameAct/Levels/Level.hpp"
#include "Edge.hpp"

namespace GameAct
{

namespace Shared
{

void
Edge::stopInteract( CharacterParts::Hip * characterHip )
{
	Director::getInstance().getGameAct()->getLevel()->updateChunks();
}

void
Edge::initialize()
{
	Area::initialize();

	Resources::LevelOrientation orientation = Director::getInstance().getGameAct()->getLevel()->getLevelOrientation();

	cocos2d::Size size = getSize();

	getBody()->removeFromWorld();
	cocos2d::PhysicsBody * body = orientation == Resources::LevelOrientation::Horizontal
	?
		cocos2d::PhysicsBody::createEdgeSegment(
		cocos2d::Vec2( size.width / -2.0f, size.height / -2.0f ),
		cocos2d::Vec2( size.width / 2.0f, size.height / -2.0f ),
		cocos2d::PHYSICSBODY_MATERIAL_DEFAULT,
		3.0f
	)
	:
		cocos2d::PhysicsBody::createEdgeSegment(
		cocos2d::Vec2( size.width / 2.0f, size.height / 2.0f ),
		cocos2d::Vec2( size.width / 2.0f, size.height / -2.0f ),
		cocos2d::PHYSICSBODY_MATERIAL_DEFAULT,
		3.0f
	);
	_representation->setPhysicsBody( body );
	body->setDynamic( false );
}

std::string
Edge::getResourcesName() const
{
	return "Edge";
}

void
Edge::separateContact( Object * object )
{
	object->stopInteract( this );
}

}

}