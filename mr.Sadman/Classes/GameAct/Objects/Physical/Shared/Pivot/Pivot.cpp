#include "Pivot.hpp"

namespace GameAct
{

namespace Physical
{

void
Pivot::initialize()
{
	Object::initialize();

	getBody()->setDynamic( false );
}

std::string
Pivot::getResourcesName() const
{
	return "Pivot";
}

void
Pivot::setAdditionalParam( std::string additionalParam )
{
	std::string rotationTime = ThirdParty::readToken( additionalParam );
	_time = atof( rotationTime.data() );

	Object::setAdditionalParam( additionalParam );
}

void
Pivot::setRotation( float angle )
{
	_angle = angle;

	Object::setRotation( angle );
}

void
Pivot::runAction( const std::string & action )
{
	if( action == "RotateSaw" )
	{
		float delta = getSize().width / 2.0f;
		float deltaX = delta * sin( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
		float deltaY = delta * cos( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
		cocos2d::Vec2 center = getPosition();
		center.x -= deltaX;
		center.y -= deltaY;
		cocos2d::Vector< cocos2d::FiniteTimeAction * > rotatePnt;
		cocos2d::Vec2 posit = getPosition();
		posit.x += deltaX;
		posit.y += deltaY;
		for( int i = 0; i < 360; ++i )
		{
			rotatePnt.pushBack( cocos2d::MoveTo::create( _time / 360, posit ) );
			posit = rotatePoint( posit, center, 1.0f );
		}
		auto action = cocos2d::RepeatForever::create( cocos2d::Sequence::create( rotatePnt ) );
		_representation->runAction( cocos2d::RepeatForever::create( action ) );
	}

	if( action == "FluctuatePendulum" )
	{
		float delta = getSize().width / 2.0f;
		float deltaX = delta * sin( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
		float deltaY = delta * cos( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
		cocos2d::Vec2 center = getPosition();
		center.x -= deltaX;
		center.y -= deltaY;
		cocos2d::Vector< cocos2d::FiniteTimeAction * > rotatePnt;
		cocos2d::Vec2 posit = getPosition();
		posit.x += deltaX;
		posit.y += deltaY;
		for( int i = 0; i < 60; ++i )
		{
			rotatePnt.pushBack( cocos2d::MoveTo::create( _time / 240, posit ) );
			posit = rotatePoint( posit, center, 1.0f );
		}
		for( int i = 0; i < 120; ++i )
		{
			rotatePnt.pushBack( cocos2d::MoveTo::create( _time / 240, posit ) );
			posit = rotatePoint( posit, center, -1.0f );
		}
		for( int i = 0; i < 60; ++i )
		{
			rotatePnt.pushBack( cocos2d::MoveTo::create( _time / 240, posit ) );
			posit = rotatePoint( posit, center, 1.0f );
		}
		auto action = cocos2d::RepeatForever::create( cocos2d::Sequence::create( rotatePnt ) );
	}

	if( action == "Stop" || action == "Off" )
	{
		_representation->setAnchorPoint( cocos2d::Vec2( 0.5f, 0.5f ) );
		_representation->stopAllActions();
	}
}

cocos2d::Vec2
Pivot::rotatePoint( cocos2d::Vec2 point, cocos2d::Vec2 center, float angle ) const
{
    angle = CC_DEGREES_TO_RADIANS( angle );
    float rotatedX = cos( angle ) * (point.x - center.x) + sin( angle ) * ( point.y - center.y ) + center.x;
    float rotatedY = -sin( angle ) * ( point.x - center.x ) + cos( angle ) * ( point.y - center.y ) + center.y;
 
    return cocos2d::Vec2( rotatedX, rotatedY );
}

}

}