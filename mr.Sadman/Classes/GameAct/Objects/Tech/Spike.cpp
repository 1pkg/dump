#include "Director.hpp"
#include "GameAct/Act.hpp"
#include "GameAct/Objects/Factories/ObjectsFactory.hpp"
#include "Spike.hpp"
#include "Resources/Cache/Cache.hpp"

namespace GameAct
{

namespace Tech
{

Spike::Spike()
	: _decorator( Director::getInstance().getGameAct()->getObjectsFactory()->create( "Line" ) )
{
}

std::string
Spike::getName() const
{
	return "Spike";
}

void
Spike::setPosition( cocos2d::Vec2 position )
{
	float koef = 1.0f / sqrt( 2.0f );
	cocos2d::Vec2 decPosit = position;
	switch ( _direction )
	{
		case Direction::Right:
			decPosit.x += _decorator->getSize().width / 2.0f;
		break;

		case Direction::Left:
			decPosit.x -= _decorator->getSize().width / 2.0f;
		break;

		case Direction::Top:
			decPosit.y += _decorator->getSize().width / 2.0f;	
		break;

		case Direction::Bottom:
			decPosit.y -= _decorator->getSize().width / 2.0f;	
		break;

		case Direction::D45:
			decPosit.y += _decorator->getSize().width / 2.0f * koef;	
			decPosit.x -= _decorator->getSize().width / 2.0f * koef;
		break;

		case Direction::D135:
			decPosit.y += _decorator->getSize().width / 2.0f * koef;	
			decPosit.x += _decorator->getSize().width / 2.0f * koef;
		break;

		case Direction::D225:
			decPosit.y -= _decorator->getSize().width / 2.0f * koef;	
			decPosit.x += _decorator->getSize().width / 2.0f * koef;
		break;

		case Direction::D315:
			decPosit.y -= _decorator->getSize().width / 2.0f * koef;	
			decPosit.x -= _decorator->getSize().width / 2.0f * koef;
		break;

		case Direction::Circle:
			decPosit.x += _decorator->getSize().width;
		break;

		default:
		break;
	}

	_decorator->setPosition( decPosit );

	Object::setPosition( position );
}

void
Spike::setSize( cocos2d::Size size )
{
	float koef = 1.0f / sqrt( 2.0f );
	cocos2d::Size decSize = size;
	switch ( _direction )
	{
		case Direction::Left:
		case Direction::Right:
		case Direction::Top:
		case Direction::Bottom:
		case Direction::Circle:
			decSize.width *= _lenth;
			decSize.height /= 2.0f;
		break;

		case Direction::D45:
		case Direction::D135:
		case Direction::D225:
		case Direction::D315:
			decSize.width *= _lenth / koef;
			decSize.height /= 2.0f;
		break;

		default:
		break;
	}
		
	_decorator->setSize( decSize );

	Object::setSize( size );
}

void
Spike::setAdditionalParam( std::string additionalParam )
{
	int posit = additionalParam.find( ';' );
	_lenth = std::stof( additionalParam.substr( 0, posit ) );
	_time = std::stof( additionalParam.substr( posit + 1, additionalParam.length() - posit - 1 ) );

	_decorator->setAdditionalParam( std::to_string( _time ) );
}

void
Spike::setDirection( Direction direction )
{
	_decorator->setDirection( direction );

	Object::setDirection( direction );
}

void
Spike::hide()
{
	_decorator->hide();

	Object::hide();
}

void
Spike::show()
{
	_decorator->hide();

	Object::show();
}

void
Spike::attachToChunk( Chunk & chunk, int zIndex )
{
	_decorator->attachToChunk( chunk, zIndex - 1 );

	Object::attachToChunk( chunk, zIndex );
}

void
Spike::runAction( const std::string & action )
{
	if( action == "Run" )
	{
		cocos2d::Vec2 pos1, pos2;
		float koef = 1.0f / sqrt( 2.0f );
		switch ( _direction )
		{
			case Direction::Right:
				pos1.x = _decorator->getSize().width;
				pos2.x = -_decorator->getSize().width;
			break;

			case Direction::Left:
				pos2.x = _decorator->getSize().width;
				pos1.x = -_decorator->getSize().width;
			break;

			case Direction::Top:
				pos1.y = _decorator->getSize().width;
				pos2.y = -_decorator->getSize().width;
			break;

			case Direction::Bottom:
				pos2.y = _decorator->getSize().width;
				pos1.y = -_decorator->getSize().width;
			break;

			case Direction::D45:
				pos2.x = _decorator->getSize().width * koef;
				pos1.x = -_decorator->getSize().width * koef;
				pos1.y = _decorator->getSize().width * koef;
				pos2.y = -_decorator->getSize().width * koef;
			break;

			case Direction::D135:
				pos1.x = _decorator->getSize().width * koef;
				pos2.x = -_decorator->getSize().width * koef;
				pos1.y = _decorator->getSize().width * koef;
				pos2.y = -_decorator->getSize().width * koef;
			break;

			case Direction::D225:
				pos1.x = _decorator->getSize().width * koef;
				pos2.x = -_decorator->getSize().width * koef;
				pos2.y = _decorator->getSize().width * koef;
				pos1.y = -_decorator->getSize().width * koef;
			break;

			case Direction::D315:
				pos2.x = _decorator->getSize().width * koef;
				pos1.x = -_decorator->getSize().width * koef;
				pos2.y = _decorator->getSize().width * koef;
				pos1.y = -_decorator->getSize().width * koef;
			break;

			default:
			break;
		}

		auto goPos1 = cocos2d::MoveBy::create( _time, pos1 );
		auto goPos2 = cocos2d::MoveBy::create( _time, pos2 );

		_sprite->runAction( cocos2d::RepeatForever::create( cocos2d::Sequence::create( goPos1, goPos2, nullptr ) ) );
		_audio = Resources::Cache::getInstance().getObjectSound( getName(), "Def" );
	}
	
	if( action == "Stop"  )
		_sprite->stopAllActions();
	
}

}

}