#include "Director.hpp"
#include "GameAct/Act.hpp"
#include "GameAct/Levels/Chunk.hpp"
#include "GameAct/Objects/Factories/ObjectsFactory.hpp"
#include "AssaultTank.hpp"
#include "Resources/Cache/Cache.hpp"

#include <spine\SkeletonAnimation.h>

namespace GameAct
{

namespace Physical
{

void
AssaultTank::initialize()
{
	Object::initialize();

	spine::SkeletonAnimation * skeleton = (spine::SkeletonAnimation *) _representation;
	skeleton->updateWorldTransform();

	auto body =  cocos2d::PhysicsBody::createBox( _representation->getContentSize() );
	/*_representation->setPhysicsBody( body );
	body->setDynamic( false );*/
}

std::string
AssaultTank::getResourcesName() const
{
	return "AssaultTank";
}

void
AssaultTank::setAdditionalParam( std::string additionalParam )
{
	std::string time = ThirdParty::readToken( additionalParam );
	_time = atof( time.data() );

	std::string shell;
	while( ( shell = ThirdParty::readToken( additionalParam ) ), !shell.empty() )
		_shells.push_back( shell );

	Object::setAdditionalParam( additionalParam );
}

void
AssaultTank::setRotation( float angle )
{
	_angle = angle;

	Object::setRotation( angle );
}

void
AssaultTank::attachToChunk( Chunk & chunk, int zIndex )
{
	_zindex = zIndex;

	Object::attachToChunk( chunk, zIndex );
}

void
AssaultTank::runAction( const std::string & action )
{
	if( action == "Fire" || action == "On" )
	{
		auto size = getSize();
		auto position = getPosition();

		spine::SkeletonAnimation * skeleton = (spine::SkeletonAnimation *) _representation;

		auto animationF = [skeleton]()
		{
			skeleton->addAnimation( 0, "fire", false );
		};

		auto animationR = [skeleton]()
		{
			skeleton->addAnimation( 0, "back", false );
		};

		auto fire = [ this, size ] ()
		{
			if( _shells.size() <= ++_current )
				_current = 0;

			auto shellSize = size;
			shellSize.width /= 10.0f;
			shellSize.height /= 10.0f;

			auto shellPosit = getPosition();
			shellPosit.y -= size.height / 2.0f * cos( CC_DEGREES_TO_RADIANS( _angle + 270.0f ) );
			shellPosit.x += size.width / 2.0f * sin( CC_DEGREES_TO_RADIANS( _angle + 270.0f ) );

			auto shell = Director::getInstance().getGameAct()->getObjectsFactory()->create( _shells[ _current ] );
			shell->setSize( shellSize );
			shell->setPosition( shellPosit );
			shell->attachToChunk( *_chunk, _zindex );

			float delta = size.width * 1000.0f;
			float deltaX = delta * sin( CC_DEGREES_TO_RADIANS( _angle + 270.0f ) );
			float deltaY = delta * cos( CC_DEGREES_TO_RADIANS( _angle + 270.0f ) );

			shell->getBody()->applyImpulse( cocos2d::Vec2( deltaX, deltaY ) );
		};

		auto action = cocos2d::Sequence::create( cocos2d::CallFunc::create( animationF ), cocos2d::CallFunc::create( fire ), cocos2d::CallFunc::create( animationR ), cocos2d::DelayTime::create( _time ), nullptr );
		_representation->runAction( cocos2d::RepeatForever::create( action ) );

		return;
	}

	if( action == "Off" )
	{
		_representation->stopAllActions();

		return;
	}

	Object::runAction( action );
}

}

}