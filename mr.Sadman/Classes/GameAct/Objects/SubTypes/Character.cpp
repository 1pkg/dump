#include "Character.hpp"
#include "Edge.hpp"
#include "Resources/Cache/Cache.hpp"

namespace GameAct
{

void
Character::interact( Edge * bg )
{
	bg->interact( this );
}

void
Character::initialize()
{
	_sprite = Resources::Cache::getInstance().getObjectSprite( getName() );
	auto body = Resources::Cache::getInstance().getObjectBody( getName(), "Def" );
	_sprite->setPhysicsBody( body );

	body->setDynamic( true );
	body->setCategoryBitmask( 0x1 << 4 ); // who ?
	body->setCollisionBitmask( 0x1 << 5 ); // with who ?
	body->setContactTestBitmask( 0x1 << 5 ); // with who ?
}

std::string
Character::getName() const
{
	return "Character";
}

cocos2d::PhysicsBody *
Character::getBody() const
{
	return _sprite->getPhysicsBody();
}

void
Character::attachToLayer( cocos2d::Layer * layer, int zIndex )
{
	layer->addChild( _sprite, zIndex );

	layer->runAction( cocos2d::Follow::create( _sprite ) );
}

void
Character::runAction( const std::string & action )
{
	if( action == "run" )
		getBody()->setVelocity( cocos2d::Vec2( 0.0f, -150.0f ) );

	if( action == "stop" )
		getBody()->setVelocity( cocos2d::Vec2( 0.0f, 0.0f ) );
}

void
Character::runInteraction( Object * object )
{
	object->interact( this );
}

}