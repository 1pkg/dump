#include "FlameThrower.hpp"
#include "Game.hpp"
#include "Game/Objects/Factories/ObjectsFactory.hpp"


namespace Objects
{

namespace Tech
{

FlameThrower::FlameThrower( Direction direction )
	: _flame( createFlame( direction ) ),
	_direction( direction )
{
}

void
FlameThrower::initialize()
{
	StaticObject::initialize();

	switch ( _direction )
	{
		case Objects::Direction::Left:
			setRotation( 180.0f );
		break;

		case Objects::Direction::Top:
			setRotation( -90.0f );
		break;

		case Objects::Direction::Bottom:
			setRotation( 90.0f );
		break;

		default:
		break;
	}

	runAction( "fire" );
}

std::string
FlameThrower::getName() const
{
	return "FlameThrower";
}

void
FlameThrower::setPosition( cocos2d::Vec2 position )
{
	cocos2d::Vec2 bulPosition = position;
	switch ( _direction )
	{
		case Objects::Direction::Right:
			bulPosition.x += getSize().width / 2;
		break;

		case Objects::Direction::Left:
			bulPosition.x -= getSize().width / 2;
		break;

		case Objects::Direction::Top:
			bulPosition.y += getSize().height / 2;
		break;

		case Objects::Direction::Bottom:
			bulPosition.y -= getSize().height / 2;
		break;

		default:
		break;
	}

	_flame->setPosition( bulPosition );

	StaticObject::setPosition( position );
}

void
FlameThrower::setSize( cocos2d::Size size )
{
	cocos2d::Size bulSize = size;
	switch ( _direction )
	{
		case Objects::Direction::Right:
		case Objects::Direction::Left:
			bulSize.width *= 3.0f;
			bulSize.height /= 1.5f;
		break;

		case Objects::Direction::Top:
		case Objects::Direction::Bottom:
			bulSize.width /= 1.5f;
			bulSize.height *= 3.0f;
		break;

		default:
		break;
	}

	_flame->setSize( bulSize );

	StaticObject::setSize( size );
}

void
FlameThrower::setRotation( float angle )
{
	if( angle == 180.0f )
	{
		_sprite->runAction( cocos2d::ScaleBy::create( 0.0f, -1.0f, 1.0f ) );
		return;
	}

	StaticObject::setRotation( angle );
}

void
FlameThrower::hide()
{
	_flame->hide();

	StaticObject::hide();
}

void
FlameThrower::show()
{
	_flame->show();

	StaticObject::show();
}

void
FlameThrower::attachToChunk( Levels::Chunk & chunk, int zIndex )
{
	_flame->attachToChunk( chunk, zIndex );

	StaticObject::attachToChunk( chunk, zIndex );
}

void
FlameThrower::runAction( const std::string & action )
{
	if( action == "stop" )
		_flame->hide();

	if( action == "fire" )
		_flame->show();
}

StaticObject *
FlameThrower::createFlame( Direction direction )
{
	std::string name = "Flame" + ( -direction );

	Object * obj = Game::getInstance()->getObjectsFactory()->create( name );
	StaticObject * stObj = dynamic_cast< StaticObject * >( obj );
	return stObj;
}

}

}