#include "RectangleRotatedBlock.hpp"

namespace GameAct
{

namespace Physical
{

void
RectangleRotatedBlock::setPosition( cocos2d::Vec2 position )
{
	_position = position;

	float delta = getSize().width * _lenth;
	float deltaX = delta * sin( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
	float deltaY = delta * cos( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
	position.x += deltaX;
	position.y += deltaY;
	RectangleStaticBlock::setPosition( position );
}

void
RectangleRotatedBlock::setAdditionalParam( std::string additionalParam )
{
	std::string lenth = ThirdParty::readToken( additionalParam );
	_lenth = atof( lenth.data() );
	std::string time = ThirdParty::readToken( additionalParam );
	_time = atof( time.data() );

	RectangleStaticBlock::setAdditionalParam( additionalParam );
}

void
RectangleRotatedBlock::setRotation( float angle )
{
	_angle = angle;

	Object::setRotation( angle );
}

void
RectangleRotatedBlock::runAction( const std::string & action )
{
	if( action == "Rotate" || action == "On" )
	{
		cocos2d::Vec2 center = _position;
		cocos2d::Vector< cocos2d::FiniteTimeAction * > rotatePnt;
		cocos2d::Vec2 posit = getPosition();
		for( int i = 0; i < 360; ++i )
		{
			rotatePnt.pushBack( cocos2d::MoveTo::create( _time / 360, posit ) );
			posit = rotatePoint( posit, center, 1.0f );
		}
		auto action = cocos2d::RepeatForever::create( cocos2d::Sequence::create( rotatePnt ) );
		_representation->runAction( action );

		return;
	}

	if( action == "Stop" || action == "Off" )
	{
		_representation->stopAllActions();

		return;
	}

	Object::runAction( action );
}

cocos2d::Vec2
RectangleRotatedBlock::rotatePoint( cocos2d::Vec2 point, cocos2d::Vec2 center, float angle ) const
{
    angle = CC_DEGREES_TO_RADIANS( angle );
    float rotatedX = cos( angle ) * (point.x - center.x) + sin( angle ) * ( point.y - center.y ) + center.x;
    float rotatedY = -sin( angle ) * ( point.x - center.x ) + cos( angle ) * ( point.y - center.y ) + center.y;
 
    return cocos2d::Vec2( rotatedX, rotatedY );
}

}

}