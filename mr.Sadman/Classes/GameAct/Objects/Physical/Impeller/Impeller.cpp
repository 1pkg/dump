#include "Director.hpp"
#include "GameAct/Act.hpp"
#include "GameAct/Objects/Factories/ObjectsFactory.hpp"
#include "Impeller.hpp"
#include "GameAct/Objects/SubTypes/Stream.hpp"

namespace GameAct
{

namespace Physical
{

Impeller::Impeller()
	: _pivot( Director::getInstance().getGameAct()->getObjectsFactory()->create( "Pivot" ) ),
	_wind( dynamic_cast< Stream * >( Director::getInstance().getGameAct()->getObjectsFactory()->create( "Wind" ) ) )
{
	_wind->hide();
}

void
Impeller::initialize()
{
	Object::initialize();

	auto body =  cocos2d::PhysicsBody::createBox( _representation->getContentSize() );
	_representation->setPhysicsBody( body );
	body->setDynamic( false );
}

std::string
Impeller::getResourcesName() const
{
	return "Impeller";
}

void
Impeller::setPosition( cocos2d::Vec2 position )
{
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


	cocos2d::Vec2 windPosition = position;
	delta = getSize().width / 2.0f;
	deltaX = delta * sin( CC_DEGREES_TO_RADIANS( _angle + 90.0f  ) );
	deltaY = delta * cos( CC_DEGREES_TO_RADIANS( _angle + 90.0f  ) );
	windPosition.x += deltaX;
	windPosition.y += deltaY;
	_wind->setPosition( windPosition );


	Object::setPosition( position );
}

void
Impeller::setSize( cocos2d::Size size )
{
	cocos2d::Size pivotSize = size;
	pivotSize.width *= _lenth;	
	_pivot->setSize( pivotSize );

	cocos2d::Size windSize = size;
	windSize.width *= _windLenth;	
	_wind->setSize( windSize );

	Object::setSize( size );
}

void
Impeller::setAdditionalParam( std::string additionalParam )
{
	std::string lenth = ThirdParty::readToken( additionalParam );
	_lenth = atof( lenth.data() );

	std::string windLenth = ThirdParty::readToken( additionalParam );
	_windLenth = atof( windLenth.data() );

	Object::setAdditionalParam( additionalParam );
}

void
Impeller::setRotation( float angle )
{
	_angle = angle;

	_pivot->setRotation( angle );

	_wind->setRotation( angle );

	Object::setRotation( angle );
}

void
Impeller::hide()
{
	_pivot->hide();

	_wind->hide();

	Object::hide();
}

void
Impeller::show()
{
	_pivot->show();

	_wind->show();

	Object::show();
}

void
Impeller::attachToChunk( Chunk & chunk, int zIndex )
{
	_pivot->attachToChunk( chunk, zIndex - 1 );

	_wind->attachToChunk( chunk, zIndex );

	Object::attachToChunk( chunk, zIndex );
}

void
Impeller::runAction( const std::string & action )
{
	if( action == "Rotate" || action == "On" )
	{
		_wind->show();

		_representation->runAction( cocos2d::RepeatForever::create( cocos2d::RotateBy::create( 1.0f, 360.0f ) ) );

		return;
	}

	if( action == "Off" )
	{
		_wind->hide();

		_representation->stopAllActions();

		return;
	}

	Object::runAction( action );
}

}

}