#include "Director.hpp"
#include "GameAct/Act.hpp"
#include "GameAct/Objects/Factories/ObjectsFactory.hpp"
#include "Impeller.hpp"
#include "GameAct/Objects/SubTypes/Stream.hpp"

namespace GameAct
{

namespace Tech
{

Impeller::Impeller()
	: _decorator( Director::getInstance().getGameAct()->getObjectsFactory()->create( "Line" ) ),
	_wind( dynamic_cast< Stream * >( Director::getInstance().getGameAct()->getObjectsFactory()->create( "Wind" ) ) )
{
}

std::string
Impeller::getName() const
{
	return "Impeller";
}

void
Impeller::setPosition( cocos2d::Vec2 position )
{
	float koef = 1.0f / sqrt( 2.0f );
	cocos2d::Vec2 decPosition = position;
	cocos2d::Vec2 windPosition = position;
	switch ( _direction )
	{
		case Direction::Left:
			windPosition.x -= getSize().width / 2.0f;
			decPosition.x += _decorator->getSize().width / 2.0f;
		break;

		case Direction::Right:
			windPosition.x += getSize().width / 2.0f;
			decPosition.x -= _decorator->getSize().width / 2.0f;
		break;

		case Direction::Top:
			windPosition.y += getSize().width / 2.0f;
			decPosition.y -= _decorator->getSize().width / 2.0f;
		break;

		case Direction::Bottom:
			windPosition.y -= getSize().width / 2.0f;
			decPosition.y += _decorator->getSize().width / 2.0f;
		break;

		case Direction::D45:
			windPosition.y += getSize().width * koef / 2.0f;
			decPosition.y -= _decorator->getSize().width * koef / 2.0f;
			windPosition.x -= getSize().width * koef / 2.0f;
			decPosition.x += _decorator->getSize().width * koef / 2.0f;
		break;

		case Direction::D135:
			windPosition.y += getSize().width * koef / 2.0f;
			decPosition.y -= _decorator->getSize().width * koef / 2.0f;
			windPosition.x += getSize().width * koef / 2.0f;
			decPosition.x -= _decorator->getSize().width * koef / 2.0f;
		break;

		case Direction::D225:
			windPosition.y -= getSize().width * koef  / 2.0f;
			decPosition.y += _decorator->getSize().width * koef / 2.0f;
			windPosition.x += getSize().width * koef / 2.0f;
			decPosition.x -= _decorator->getSize().width * koef / 2.0f;
		break;

		case Direction::D315:
			windPosition.y -= getSize().width * koef / 2.0f;
			decPosition.y += _decorator->getSize().width * koef / 2.0f;
			windPosition.x -= getSize().width * koef / 2.0f;
			decPosition.x += _decorator->getSize().width * koef / 2.0f;
		break;

		default:
		break;
	}

	_wind->setPosition( windPosition );
	_decorator->setPosition( decPosition );
	
	Object::setPosition( position );
}

void
Impeller::setSize( cocos2d::Size size )
{
	cocos2d::Size decSize = size;
	cocos2d::Size windSize = size;

	float koef = 1.0f / sqrt( 2.0f );
	switch ( _direction )
	{
		case Direction::Left:
		case Direction::Right:
		case Direction::Top:
		case Direction::Bottom:
		case Direction::Circle:
			decSize.width *= _lenth;
			decSize.height /= 2.0f;
			windSize.width *= _windLenth;
			windSize.height *= _windLenth / 1.75f;
		break;

		case Direction::D45:
		case Direction::D135:
		case Direction::D225:
		case Direction::D315:
			decSize.width *= _lenth / koef;
			decSize.height /= 2.0f;
			windSize.width *= _windLenth / koef;
			windSize.height *= _windLenth / 1.75f;
		break;

		default:
		break;
	}

	_decorator->setSize( decSize );
	_wind->setSize( windSize );

	Object::setSize( size );
}

void
Impeller::setAdditionalParam( std::string additionalParam )
{
	int posit = additionalParam.find( ';' );
	_lenth = std::stof( additionalParam.substr( 0, posit ) );
	_windLenth = std::stof( additionalParam.substr( posit + 1, additionalParam.length() - posit - 1 ) );
}

void
Impeller::setDirection( Direction direction )
{
	_decorator->setDirection( direction );

	_wind->setDirection( direction );

	Object::setDirection( direction );
}

void
Impeller::hide()
{
	_decorator->hide();

	_wind->hide();

	Object::hide();
}

void
Impeller::show()
{
	_decorator->show();

	_wind->show();

	Object::show();
}

void
Impeller::attachToChunk( Chunk & chunk, int zIndex )
{
	_decorator->attachToChunk( chunk, zIndex - 1 );

	_wind->attachToChunk( chunk, zIndex );

	Object::attachToChunk( chunk, zIndex );
}

void
Impeller::runAction( const std::string & action )
{
	if( action == "Run" )
	{
		show();
		_sprite->runAction( cocos2d::RepeatForever::create( cocos2d::RotateBy::create( 1.0f, -360.0f ) ) );
	}

	if( action == "Stop" )
	{
		_sprite->stopAllActions();
		_decorator->hide();
		_wind->hide();
	}
}

}

}