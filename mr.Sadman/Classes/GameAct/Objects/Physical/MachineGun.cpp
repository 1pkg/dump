#include "Director.hpp"
#include "GameAct/Act.hpp"
#include "GameAct/Objects/Factories/ObjectsFactory.hpp"
#include "MachineGun.hpp"
#include "GameAct/Objects/SubTypes/Stream.hpp"
#include "Resources/Cache/Cache.hpp"


namespace GameAct
{

namespace Physical
{

MachineGun::MachineGun( )
	: _bullets( dynamic_cast< Stream * >( Director::getInstance().getGameAct()->getObjectsFactory()->create( "Bullets" ) ) )
{
	_bullets->hide();
}

std::string
MachineGun::getName() const
{
	return "MachineGun";
}

void
MachineGun::setPosition( cocos2d::Vec2 position )
{
	cocos2d::Vec2 bulPosition = position;
	float delta = getSize().width / 2.0f;
	float deltaX = delta * sin( CC_DEGREES_TO_RADIANS( _angle + 90.0f  ) );
	float deltaY = delta * cos( CC_DEGREES_TO_RADIANS( _angle + 90.0f  ) );
	bulPosition.x += deltaX;
	bulPosition.y += deltaY;
	_bullets->setPosition( bulPosition );

	Object::setPosition( position );
}

void
MachineGun::setSize( cocos2d::Size size )
{
	cocos2d::Size bulSize = size;
	bulSize.width *= _lenth;
	bulSize.height /= _lenth / 1.75f;		
	_bullets->setSize( bulSize );

	Object::setSize( size );
}

void
MachineGun::setAdditionalParam( std::string additionalParam )
{
	_lenth = atof( additionalParam.data() );

	Object::setAdditionalParam( additionalParam );
}

void
MachineGun::setRotation( float angle )
{
	_angle = angle;

	Object::setRotation( angle );
}

void
MachineGun::setScale( cocos2d::Vec2 scale )
{
	if( scale.x == -1.0f || scale.y == -1.0f )
		_angle += 180.0f;

	Object::setScale( scale );
}

void
MachineGun::hide()
{
	_bullets->hide();

	Object::hide();
}

void
MachineGun::attachToChunk( Chunk & chunk, int zIndex )
{
	_bullets->attachToChunk( chunk, zIndex );

	Object::attachToChunk( chunk, zIndex );
}

void
MachineGun::runAction( const std::string & action )
{
	if( action == "Fire" )
	{
		auto size = getSize();
		setSize( _sprite->getContentSize() );
		auto fire = Resources::Cache::getInstance().getObjectAnimation( getName(), "Fire" );
		_sprite->runAction( fire );
		setSize( size );

		_bullets->show();

		return;
	}

	if( action == "Stop" )
	{
		_sprite->stopAllActions();
		_bullets->hide();

		return;
	}

	Object::runAction( action );
}

}

}