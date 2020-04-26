#include "Director.hpp"
#include "GameAct/Act.hpp"
#include "GameAct/Levels/Chunk.hpp"
#include "GameAct/Objects/Factories/ObjectsFactory.hpp"
#include "PneumaticGun.hpp"
#include "GameAct/Objects/SubTypes/Stream.hpp"
#include "Resources/Cache/Cache.hpp"

namespace GameAct
{

namespace Physical
{

PneumaticGun::PneumaticGun()
	: _wind( dynamic_cast< Stream * >( Director::getInstance().getGameAct()->getObjectsFactory()->create( "Wind" ) ) )
{
	_wind->hide();
}

void
PneumaticGun::initialize()
{
	Object::initialize();

	getBody()->setDynamic( false );
}

std::string
PneumaticGun::getResourcesName() const
{
	return "PneumaticGun";
}

void
PneumaticGun::setPosition( cocos2d::Vec2 position )
{
	cocos2d::Vec2 windPosition = position;
	float deltaWind = getSize().width / 2.0f;
	float deltaXWind = deltaWind * sin( CC_DEGREES_TO_RADIANS( _angle + 90.0f  ) );
	float deltaYWind = deltaWind * cos( CC_DEGREES_TO_RADIANS( _angle + 90.0f  ) );
	windPosition.x += deltaXWind;
	windPosition.y += deltaYWind;
	_wind->setPosition( windPosition );

	Object::setPosition( position );
}

void
PneumaticGun::setSize( cocos2d::Size size )
{
	cocos2d::Size windSize = size;
	windSize.width /= 8.0f;
	windSize.height /= 8.0f;		
	_wind->setSize( windSize );

	Object::setSize( size );
}

void
PneumaticGun::setAdditionalParam( std::string additionalParam )
{
	std::string time = ThirdParty::readToken( additionalParam );
	_time = atof( time.data() );

	std::string shell;
	while( ( shell = ThirdParty::readToken( additionalParam ) ), !shell.empty() )
		_shells.push_back( shell );

	Object::setAdditionalParam( additionalParam );
}

void
PneumaticGun::setRotation( float angle )
{
	_angle = angle;

	_wind->setRotation( angle );

	Object::setRotation( angle );
}

void
PneumaticGun::hide()
{
	_wind->hide();

	Object::hide();
}

void
PneumaticGun::show()
{
	_wind->show();

	Object::show();
}

void
PneumaticGun::attachToChunk( Chunk & chunk, int zIndex )
{
	_zindex = zIndex;

	_wind->attachToChunk( chunk, zIndex );

	Object::attachToChunk( chunk, zIndex );
}

void
PneumaticGun::runAction( const std::string & action )
{
	if( action == "Fire" || action == "On" )
	{
		auto size = getSize();
		auto position = getPosition();
		setSize( _representation->getContentSize() );

		auto animationF = Resources::Cache::getInstance().getObjectAnimation( getResourcesName(), "Fire" );
		auto animationR = Resources::Cache::getInstance().getObjectAnimation( getResourcesName(), "Reset" );

		unsigned int current = 0;
		auto fire = [ this, &current, size ] ()
		{
			if( _shells.size() < ++current )
				current = 0;

			auto shellSize = size;
			shellSize.width /= 10.0f;
			shellSize.height /= 10.0f;

			auto shell = Director::getInstance().getGameAct()->getObjectsFactory()->create( _shells[ current ] );
			shell->setSize( shellSize );
			shell->setPosition( getPosition() );
			shell->attachToChunk( *_chunk, _zindex );

			float delta = size.width * 100.0f;
			float deltaX = delta * sin( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
			float deltaY = delta * cos( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );

			shell->getBody()->applyImpulse( cocos2d::Vec2( deltaX, deltaY ) );

			_wind->showFor( 0.5f );

			Resources::Cache::getInstance().getObjectAudio( getResourcesName(), "Push" );
		};

		auto action = cocos2d::Sequence::create( animationF, cocos2d::CallFunc::create( fire ), animationR, cocos2d::DelayTime::create( _time ), nullptr );
		_representation->runAction( cocos2d::RepeatForever::create( action ) );
		setSize( size );

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