#include "Spring.hpp"

namespace GameAct
{

namespace Physical
{

void
Spring::initialize()
{
	Object::initialize();

	auto body =  cocos2d::PhysicsBody::createBox( _representation->getContentSize() );
	_representation->setPhysicsBody( body );
	body->setDynamic( false );
}

std::string
Spring::getResourcesName() const
{
	return "Spring";
}

void
Spring::setRotation( float angle )
{
	_angle = angle;

	Object::setRotation( angle );
}

void
Spring::runAction( const std::string & action )
{
	if( action == "Press" || action == "On" )
	{
		float delta = 0.5f;
		float deltaX = 1.0f - delta * sin( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
		float deltaY = 1.0f - delta * cos( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
		auto action = cocos2d::ScaleBy::create( 0.5f, deltaX, deltaY, 1.0f );
		_representation->runAction( action );

		return;
	}

	if( action == "Realese" || action == "Off" )
	{
		float delta = 2.0f;
		float deltaX = 1.0f - delta * sin( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
		float deltaY = 1.0f - delta * cos( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
		auto action = cocos2d::ScaleBy::create( 0.5f, deltaX, deltaY, 1.0f );
		_representation->runAction( action );

		return;
	}

	Object::runAction( action );
}

}

}