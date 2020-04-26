#include "Director.hpp"
#include "GameAct/Act.hpp"
#include "GameAct/Objects/Factories/ObjectsFactory.hpp"
#include "RotatedSaw.hpp"

namespace GameAct
{

namespace Physical
{

RotatedSaw::RotatedSaw()
	: _pivot( Director::getInstance().getGameAct()->getObjectsFactory()->create( "Pivot" ) )
{
}

void
RotatedSaw::setPosition( cocos2d::Vec2 position )
{
	_position = position;

	cocos2d::Vec2 pivotPosit = position;
	float delta = _pivot->getSize().width / 2.0f;
	float deltaX = delta * sin( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
	float deltaY = delta * cos( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
	pivotPosit.x += deltaX;
	pivotPosit.y += deltaY;
	_pivot->setPosition( pivotPosit );


	delta = getSize().width * _lenth;
	deltaX = delta * sin( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
	deltaY = delta * cos( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
	position.x += deltaX;
	position.y += deltaY;

	Object::setPosition( position );
}

void
RotatedSaw::setSize( cocos2d::Size size )
{
	cocos2d::Size pivotSize = size;
	pivotSize.width *= _lenth;	
	_pivot->setSize( pivotSize );

	Object::setSize( size );
}

void
RotatedSaw::setAdditionalParam( std::string additionalParam )
{
	std::string lenth = ThirdParty::readToken( additionalParam );
	_lenth = atof( lenth.data() );
	std::string time = ThirdParty::readToken( additionalParam );
	_time = atof( time.data() );

	_pivot->setAdditionalParam( time );

	Object::setAdditionalParam( additionalParam );
}

void
RotatedSaw::setRotation( float angle )
{
	_angle = angle;

	_pivot->setRotation( angle );

	Object::setRotation( angle );
}

void
RotatedSaw::hide()
{
	_pivot->hide();

	Object::hide();
}

void
RotatedSaw::show()
{
	_pivot->show();

	Object::show();
}

void
RotatedSaw::attachToChunk( Chunk & chunk, int zIndex )
{
	_pivot->attachToChunk( chunk, zIndex - 1 );

	Object::attachToChunk( chunk, zIndex );
}

void
RotatedSaw::runAction( const std::string & action )
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
		auto rotate = cocos2d::RotateBy::create( _time, 360.0f );
		auto action = cocos2d::RepeatForever::create( cocos2d::Spawn::create( rotate, cocos2d::Sequence::create( rotatePnt ), nullptr ) );
		_representation->runAction( action );

		_pivot->runAction( "RotateSaw" );

		_audio->resume();

		return;
	}

	if( action == "Stop" || action == "Off" )
	{
		_representation->stopAllActions();

		_pivot->runAction( "Stop" );

		_audio->pause();

		return;
	}

	Object::runAction( action );
}

cocos2d::Vec2
RotatedSaw::rotatePoint( cocos2d::Vec2 point, cocos2d::Vec2 center, float angle ) const
{
    angle = CC_DEGREES_TO_RADIANS( angle );
    float rotatedX = cos( angle ) * (point.x - center.x) + sin( angle ) * ( point.y - center.y ) + center.x;
    float rotatedY = -sin( angle ) * ( point.x - center.x ) + cos( angle ) * ( point.y - center.y ) + center.y;
 
    return cocos2d::Vec2( rotatedX, rotatedY );
}

}

}