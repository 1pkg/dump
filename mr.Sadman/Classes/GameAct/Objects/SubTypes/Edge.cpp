#include "Director.hpp"
#include "GameAct/Act.hpp"
#include "GameAct/Levels/Level.hpp"
#include "Edge.hpp"

namespace GameAct
{

void
Edge::interact( Character * sadman )
{
	Director::getInstance().getGameAct()->getLevel()->updateChunks();
}

void
Edge::initialize()
{
	cocos2d::Size size = cocos2d::Size( 64.0f, 64.0f );
	_sprite = cocos2d::Sprite::create();
	_sprite->setContentSize( size );

	cocos2d::PhysicsBody * body = cocos2d::PhysicsBody::createEdgeSegment(
		cocos2d::Vec2( size.width / -2.0, size.height / -2.0 ), cocos2d::Vec2( size.width / 2.0, size.height / -2.0 ), cocos2d::PHYSICSBODY_MATERIAL_DEFAULT, 3.0f
	);	
	_sprite->setPhysicsBody( body );

	body->setDynamic( false );
	body->setCategoryBitmask( 0x1 << 5 ); // who ?
	body->setCollisionBitmask( 0x1 << 6 ); // with who ?
	body->setContactTestBitmask( 0x1 << 4 ); // with who ?
}

std::string
Edge::getName() const
{
	return "Edge";
}

void
Edge::runInteraction( Object * object )
{
	object->interact( this );
}

}