#include "Director.hpp"
#include "GameAct/Act.hpp"
#include "GameAct/Objects/Factories/ObjectsFactory.hpp"
#include "Pump.hpp"
#include "GameAct/Objects/SubTypes/Stream.hpp"
#include "Resources/Cache/Cache.hpp"

namespace GameAct
{

namespace Physical
{

Pump::Pump()
	: _wind( dynamic_cast< Stream * >( Director::getInstance().getGameAct()->getObjectsFactory()->create( "Wind" ) ) )
{
	_wind->hide();
}

void
Pump::initialize()
{
	Object::initialize();

	getBody()->setDynamic( false );

	_audio = Resources::Cache::getInstance().getObjectAudio( getResourcesName(), "Pull" );
	_audio->setLoop( true );
	_audio->pause();
}

std::string
Pump::getResourcesName() const
{
	return "Pump";
}

void
Pump::setPosition( cocos2d::Vec2 position )
{
	cocos2d::Vec2 windPosition = position;
	float deltaWind = getSize().width / 2.0f;
	float deltaXWind = deltaWind * sin( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
	float deltaYWind = deltaWind * cos( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
	windPosition.x += deltaXWind;
	windPosition.y += deltaYWind;
	_wind->setPosition( windPosition );

	Object::setPosition( position );
}

void
Pump::setSize( cocos2d::Size size )
{
	cocos2d::Size windSize = size;
	windSize.width *= _windLenth;
	_wind->setSize( windSize );

	Object::setSize( size );
}

void
Pump::setAdditionalParam( std::string additionalParam )
{
	std::string windLenth = ThirdParty::readToken( additionalParam );
	_windLenth = atof( windLenth.data() );

	Object::setAdditionalParam( additionalParam );
}

void
Pump::setRotation( float angle )
{
	_angle = angle;

	_wind->setRotation( angle + 180.0f );

	Object::setRotation( angle );
}

void
Pump::hide()
{
	_wind->hide();

	Object::hide();
}

void
Pump::show()
{
	_wind->show();

	Object::show();
}

void
Pump::attachToChunk( Chunk & chunk, int zIndex )
{

	_wind->attachToChunk( chunk, zIndex );

	Object::attachToChunk( chunk, zIndex );
}

void
Pump::runAction( const std::string & action )
{
	if( action == "Pull" || action == "On" )
	{
		_wind->show();

		_audio->resume();

		return;
	}

	if( action == "Off" )
	{
		_wind->hide();

		_audio->pause();

		return;
	}

	Object::runAction( action );
}

}

}