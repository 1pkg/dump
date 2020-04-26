#include "Button.hpp"

namespace GameAct
{

namespace Physical
{

void
Button::initialize()
{
	Object::initialize();

	auto body =  cocos2d::PhysicsBody::createBox( _representation->getContentSize() );
	_representation->setPhysicsBody( body );
	body->setDynamic( false );
}

std::string
Button::getResourcesName() const
{
	return "Button";
}

void
Button::setRotation( float angle )
{
	_angle = angle;

	Object::setRotation( angle );
}

void
Button::runAction( const std::string & action )
{
	if( action == "Press" )
	{
		float delta = 0.5f;
		float deltaX = 1.0f - delta * sin( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
		float deltaY = 1.0f - delta * cos( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
		auto actionOne = cocos2d::ScaleBy::create( 0.5f, deltaX, deltaY, 1.0f );
		auto acttionTwo = cocos2d::ScaleBy::create( 0.5f, 1.0f / deltaX, 1.0f / deltaY, 1.0f );

		auto onIt = [ this ] ()
		{
			for( auto obj : _slaves )
				obj->runAction( "On" );		
		};

		auto runSeq = cocos2d::Sequence::create( actionOne, cocos2d::CallFunc::create( onIt ), cocos2d::DelayTime::create( 0.5f ), acttionTwo, nullptr );
		_representation->runAction( runSeq );

		return;
	}

	Object::runAction( action );
}

}

}