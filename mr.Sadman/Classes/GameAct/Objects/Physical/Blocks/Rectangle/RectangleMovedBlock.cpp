#include "RectangleMovedBlock.hpp"

namespace GameAct
{

namespace Physical
{

void
RectangleMovedBlock::setPosition( cocos2d::Vec2 position )
{
	_position = position;

	RectangleStaticBlock::setPosition( position );
}

void
RectangleMovedBlock::setAdditionalParam( std::string additionalParam )
{
	std::string lenth = ThirdParty::readToken( additionalParam );
	_lenth = atof( lenth.data() );
	std::string time = ThirdParty::readToken( additionalParam );
	_time = atof( time.data() );

	RectangleStaticBlock::setAdditionalParam( additionalParam );
}

void
RectangleMovedBlock::setRotation( float angle )
{
	_angle = angle;

	Object::setRotation( angle );
}

void
RectangleMovedBlock::runAction( const std::string & action )
{
	if( action == "Move" || action == "On" )
	{
		float delta = getSize().width * _lenth;
		float deltaX = delta * sin( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
		float deltaY = delta * cos( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
		cocos2d::Vec2 positionOne( deltaX + _position.x, deltaY + _position.y );
		cocos2d::Vec2 positionTwo( -deltaX + _position.x, -deltaY + _position.y );

		auto go = cocos2d::MoveTo::create( _time, positionOne );
		auto back = cocos2d::MoveTo::create( _time, positionTwo );
		auto endlessAction = cocos2d::RepeatForever::create( cocos2d::Sequence::create( go, back, nullptr ) );
		
		auto myPosition = getPosition();
		auto initAction = myPosition.distance( positionOne ) <= myPosition.distance( positionTwo )
		? cocos2d::MoveTo::create( _time * myPosition.distance( positionOne ) / positionOne.distance( positionTwo ), positionOne )
		: cocos2d::MoveTo::create( _time * myPosition.distance( positionTwo ) / positionOne.distance( positionTwo ), positionTwo );
			
		_representation->runAction( cocos2d::Sequence::create( initAction, endlessAction, nullptr ) );

		return;
	}

	if( action == "Stop" || action == "Off" )
	{
		_representation->stopAllActions();

		return;
	}

	Object::runAction( action );
}

}

}