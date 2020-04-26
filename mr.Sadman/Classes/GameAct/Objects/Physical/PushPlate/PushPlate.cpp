#include "PushPlate.hpp"

namespace GameAct
{

namespace Physical
{

void
PushPlate::setRotation( float angle )
{
	_angle += 90.0f;

	Object::setRotation( angle + 90.0f );
}

void
PushPlate::runAction( const std::string & action )
{
	if( action == "Push" )
	{
		float delta = 0.5f;
		float deltaX = 1.0f - delta * sin( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
		float deltaY = 1.0f - delta * cos( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
		auto animation = cocos2d::ScaleBy::create( 0.5f, deltaX, deltaY, 1.0f );

		auto onIt = [ this ] ()
		{
			for( auto obj : _slaves )
				obj->runAction( "On" );		
		};

		auto action = cocos2d::Sequence::create( animation, cocos2d::CallFunc::create( onIt ), nullptr );
		_representation->runAction( action );

		return;
	}

	if( action == "Release" )
	{
		float delta = 2.0f;
		float deltaX = 1.0f - delta * sin( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
		float deltaY = 1.0f - delta * cos( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
		auto animation = cocos2d::ScaleBy::create( 0.5f, deltaX, deltaY, 1.0f );

		auto offIt = [ this ] ()
		{
			for( auto obj : _slaves )
				obj->runAction( "Off" );		
		};

		auto action = cocos2d::Sequence::create( animation, cocos2d::CallFunc::create( offIt ), nullptr );
		_representation->runAction( action );

		return;
	}

	Object::runAction( action );
}

}

}