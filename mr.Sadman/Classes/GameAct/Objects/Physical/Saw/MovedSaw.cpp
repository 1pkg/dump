#include "Director.hpp"
#include "GameAct/Act.hpp"
#include "GameAct/Objects/Factories/ObjectsFactory.hpp"
#include "MovedSaw.hpp"

namespace GameAct
{

namespace Physical
{

MovedSaw::MovedSaw()
	: _pivot( Director::getInstance().getGameAct()->getObjectsFactory()->create( "Pivot" ) )
{
}

void
MovedSaw::setPosition( cocos2d::Vec2 position )
{
	_postion = position;

	cocos2d::Vec2 pivotPosit = position;
	float delta = getSize().width * _lenth / 2.0f;
	float deltaX = delta * sin( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
	float deltaY = delta * cos( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
	pivotPosit.x += deltaX;
	pivotPosit.y += deltaY;
	_pivot->setPosition( pivotPosit );

	Object::setPosition( position );
}

void
MovedSaw::setSize( cocos2d::Size size )
{
	cocos2d::Size pivotSize = size;
	pivotSize.width *= _lenth;
	_pivot->setSize( pivotSize );

	Object::setSize( size );
}

void
MovedSaw::setAdditionalParam( std::string additionalParam )
{
	std::string lenth = ThirdParty::readToken( additionalParam );
	_lenth = atof( lenth.data() );

	std::string time = ThirdParty::readToken( additionalParam );
	_time = atof( time.data() );

	_pivot->setAdditionalParam( time );

	Object::setAdditionalParam( additionalParam );
}

void
MovedSaw::setRotation( float angle )
{
	_angle = angle;

	_pivot->setRotation( angle );

	Object::setRotation( angle );
}

void
MovedSaw::hide()
{
	_pivot->hide();

	Object::hide();
}

void
MovedSaw::show()
{
	_pivot->show();

	Object::show();
}

void
MovedSaw::attachToChunk( Chunk & chunk, int zIndex )
{
	_pivot->attachToChunk( chunk, zIndex - 1 );

	Object::attachToChunk( chunk, zIndex );
}

void
MovedSaw::runAction( const std::string & action )
{
	if( action == "Move" || action == "On" )
	{
		float delta = getSize().width * _lenth;
		float deltaX = delta * sin( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
		float deltaY = delta * cos( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
		cocos2d::Vec2 positionOne( deltaX + _postion.x, deltaY + _postion.y );
		cocos2d::Vec2 positionTwo( -deltaX + _postion.x, -deltaY + _postion.y );

		auto rotate = cocos2d::RotateBy::create( _time, 360.0f );
		auto go = cocos2d::MoveTo::create( _time * 5.0f, positionOne );
		auto back = cocos2d::MoveTo::create( _time * 5.0f, positionTwo );
		auto actionOne = cocos2d::Spawn::create( cocos2d::Repeat::create( rotate, 5 ), go, nullptr );
		auto actionTwo = cocos2d::Spawn::create( cocos2d::Repeat::create( rotate, 5 ), back, nullptr );
		auto endlessAction = cocos2d::RepeatForever::create( cocos2d::Sequence::create( actionOne, actionTwo, nullptr ) );

		auto myPosition = getPosition();
		auto initAction = myPosition.distance( positionOne ) <= myPosition.distance( positionTwo )
		? cocos2d::MoveTo::create( _time * myPosition.distance( positionOne ) / positionOne.distance( positionTwo ), positionOne )
		: cocos2d::MoveTo::create( _time * myPosition.distance( positionTwo ) / positionOne.distance( positionTwo ), positionTwo );

		_representation->runAction( cocos2d::Sequence::create( initAction, endlessAction, nullptr ) );

		_audio->resume();

		return;
	}

	if( action == "Stop" || action == "Off" )
	{
		_representation->stopAllActions();

		_audio->pause();

		return;
	}

	Object::runAction( action );
}

}

}