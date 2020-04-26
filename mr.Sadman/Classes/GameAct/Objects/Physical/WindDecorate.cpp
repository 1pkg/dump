#include "WindDecorate.hpp"
#include "Game/Objects/StaticObject.hpp"
#include "Game.hpp"
#include "Game/Objects/Factories/ObjectsFactory.hpp"

namespace Objects
{

namespace Tech
{

WindDecorate::WindDecorate( Direction direction )
	: _wind( createWind( direction ) ),
	_direction( direction )
{
}

void
WindDecorate::initialize()
{
	DecorateObject::initialize();

	setRotation( +_direction );

	auto scaleBy1 = cocos2d::ScaleBy::create( 1.0f, 1.25f, 1.0f );
	auto scaleBy2 = cocos2d::ScaleBy::create( 1.0f, 0.8f, 1.0f );
	auto sequence = cocos2d::RepeatForever::create( cocos2d::Sequence::create( scaleBy1, scaleBy2, nullptr ) );
	_sprite->runAction( sequence );
}

std::string
WindDecorate::getName() const
{
	return "WindDecorate";
}

void
WindDecorate::setPosition( cocos2d::Vec2 position )
{
	cocos2d::Vec2 windPosition = position;
	switch ( _direction )
	{
		case Objects::Direction::Right:
			windPosition.x += getSize().width;
		break;

		case Objects::Direction::Left:
			windPosition.x -= getSize().width;
		break;

		case Objects::Direction::Top:
			windPosition.y += getSize().height;
		break;

		case Objects::Direction::Bottom:
			windPosition.y -= getSize().height;
		break;

		default:
		break;
	}

	_wind->setPosition( windPosition );
	
	DecorateObject::setPosition( position );
}

void
WindDecorate::setSize( cocos2d::Size size )
{
	cocos2d::Size windSize = size;
	switch ( _direction )
	{
		case Objects::Direction::Right:
		case Objects::Direction::Left:
		case Objects::Direction::Top:
		case Objects::Direction::Bottom:
			windSize.width *= 3.0f;
			windSize.height *= 1.5f;
		break;

		default:
		break;
	}

	_wind->setSize( windSize );

	DecorateObject::setSize( size );
}

void
WindDecorate::hide()
{
	_wind->hide();

	DecorateObject::hide();
}

void
WindDecorate::show()
{
	_wind->show();

	DecorateObject::show();
}

void
WindDecorate::attachToChunk( Levels::Chunk & chunk, int zIndex )
{
	_wind->attachToChunk( chunk, zIndex + 1 );

	DecorateObject::attachToChunk( chunk, zIndex );
}

void
WindDecorate::runAction( const std::string & action )
{
}

StaticObject *
WindDecorate::createWind( Direction direction )
{
	std::string name = "Wind" + ( -direction );

	Object * obj = Game::getInstance()->getObjectsFactory()->create( name );
	StaticObject * stObj = dynamic_cast< StaticObject * >( obj );
	return stObj;
}

}

}