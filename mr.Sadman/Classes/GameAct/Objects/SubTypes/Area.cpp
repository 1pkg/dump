#include "Area.hpp"
#include "Resources/Cache/Cache.hpp"

namespace GameAct
{

void
Area::initialize()
{
	_representation = cocos2d::Sprite::create();
	_representation->setContentSize( cocos2d::Size( 64.0f, 64.0f ) );
	auto body = cocos2d::PhysicsBody::createBox( _representation->getContentSize() );
	_representation->setPhysicsBody( body );
	_audio = Resources::Cache::getInstance().getObjectAudio( getResourcesName() );

	body->setDynamic( false );
}

}