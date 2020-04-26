#include "MachineGun.hpp"
#include "Game.hpp"
#include "Game/Objects/Factories/ObjectsFactory.hpp"
#include "Game/Cache/GameCache.hpp"


namespace Objects
{

namespace Tech
{

MachineGun::MachineGun( Direction direction )
	: _bullets( createBullets( direction ) ),
	_direction( direction )
{
}

void
MachineGun::initialize()
{
	StaticObject::initialize();

	setRotation( +_direction );

	runAction( "fire" );
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
	switch ( _direction )
	{
		case Objects::Direction::Right:
			bulPosition.x += getSize().width / 2;
			bulPosition.y += getSize().width * 0.01f;
		break;

		case Objects::Direction::Left:
			bulPosition.x -= getSize().width / 2;
			bulPosition.y += getSize().width * 0.01f;
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

	_bullets->setPosition( bulPosition );

	StaticObject::setPosition( position );
}

void
MachineGun::setSize( cocos2d::Size size )
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

	_bullets->setSize( bulSize );

	StaticObject::setSize( size );
}

void
MachineGun::setRotation( float angle )
{
	if( angle == 180.0f )
	{
		_sprite->runAction( cocos2d::ScaleBy::create( 0.0f, -1.0f, 1.0f ) );
		return;
	}

	StaticObject::setRotation( angle );
}

void
MachineGun::hide()
{
	_bullets->hide();

	StaticObject::hide();
}

void
MachineGun::show()
{
	_bullets->show();

	StaticObject::show();
}

void
MachineGun::attachToChunk( Levels::Chunk & chunk, int zIndex )
{
	_bullets->attachToChunk( chunk, zIndex );

	StaticObject::attachToChunk( chunk, zIndex );
}

void
MachineGun::runAction( const std::string & action )
{
	if( action == "stop" )
	{
		_sprite->stopAllActions();

		_bullets->hide();
	}

	if( action == "fire" )
	{
		cocos2d::Vec2 pos1, pos2;
		switch ( _direction )
		{
			case Objects::Direction::Right:
			case Objects::Direction::Left:
				pos1.x = getSize().width * 0.01f;
				pos2.x = getSize().width * -0.01f;
			break;

			case Objects::Direction::Top:
			case Objects::Direction::Bottom:
				pos1.y = getSize().width * 0.01f;
				pos2.y = getSize().width * -0.01f;
			break;

			default:
			break;
		}

		auto size = getSize();
		setSize( _sprite->getContentSize() );

		auto rotate = Game::getInstance()->getGameCache()->getObjectAnimation( getName(), "Rotate" );

		auto goPos1 = cocos2d::MoveBy::create( 0.05f, pos1 );
		auto goPos2 = cocos2d::MoveBy::create( 0.05f, pos2 );

		auto sequence = cocos2d::RepeatForever::create(
			cocos2d::Spawn::create( cocos2d::Repeat::create( rotate, 2 ), cocos2d::Sequence::create( goPos1, goPos2, nullptr ), nullptr )
		);

		_sprite->runAction( sequence );
		setSize( size );

		_bullets->show();
	}
}

StaticObject *
MachineGun::createBullets( Direction direction )
{
	std::string name = "Bullets" + ( -direction );

	Object * obj = Game::getInstance()->getObjectsFactory()->create( name );
	StaticObject * stObj = dynamic_cast< StaticObject * >( obj );
	return stObj;
}

}

}