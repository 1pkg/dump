#include "Director.hpp"
#include "GameAct/Act.hpp"
#include "GameAct/Objects/Factories/ObjectsFactory.hpp"
#include "AirGun.hpp"
#include "GameAct/Objects/SubTypes/Stream.hpp"
#include "Resources/Cache/Cache.hpp"

namespace GameAct
{

namespace Physical
{

AirGun::AirGun()
	: _wind( dynamic_cast< Stream * >( Director::getInstance().getGameAct()->getObjectsFactory()->create( "Wind" ) ) )
{
}

void
AirGun::initialize()
{
	Object::initialize();

	getBody()->setDynamic( false );
}

std::string
AirGun::getResourcesName() const
{
	return "AirGun";
}

void
AirGun::setPosition( cocos2d::Vec2 position )
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
AirGun::setSize( cocos2d::Size size )
{
	cocos2d::Size windSize = size;
	windSize.width *= _windLenth;	
	_wind->setSize( windSize );

	Object::setSize( size );
}

void
AirGun::setAdditionalParam( std::string additionalParam )
{
	std::string windLenth = ThirdParty::readToken( additionalParam );
	_windLenth = atof( windLenth.data() );
	std::string time = ThirdParty::readToken( additionalParam );
	_time = atof( time.data() );

	Object::setAdditionalParam( additionalParam );
}

void
AirGun::setRotation( float angle )
{
	_angle = angle;

	_wind->setRotation( angle );

	Object::setRotation( angle );
}

void
AirGun::hide()
{
	_wind->hide();

	Object::hide();
}

void
AirGun::show()
{
	_wind->show();

	Object::show();
}

void
AirGun::attachToChunk( Chunk & chunk, int zIndex )
{
	_wind->attachToChunk( chunk, zIndex );

	Object::attachToChunk( chunk, zIndex );
}

void
AirGun::runAction( const std::string & action )
{
	if( action == "Push" || action == "On" )
	{
		auto push = [ this ]()
		{
			_wind->showFor( _time / 2.0f );
			Resources::Cache::getInstance().getObjectAudio( getResourcesName(), "Push" );
		};
		auto action = cocos2d::Sequence::create( cocos2d::CallFunc::create( push ), cocos2d::DelayTime::create( _time ), nullptr );
		_representation->runAction( cocos2d::RepeatForever::create( action ) );		

		return;
	}

	if( action == "Off" )
	{
		_representation->stopAllActions();

		return;
	}

	Object::runAction( action );
}

}

}