#include "Director.hpp"
#include "GameAct/Act.hpp"
#include "GameAct/Objects/Factories/ObjectsFactory.hpp"
#include "Saw.hpp"
#include "Resources/Cache/Cache.hpp"

#include <cmath>

namespace GameAct
{

namespace Tech
{

Saw::Saw()
	: _decorator( Director::getInstance().getGameAct()->getObjectsFactory()->create( "Line" ) )
{
}

std::string
Saw::getName() const
{
	return "Saw";
}

void
Saw::setPosition( cocos2d::Vec2 position )
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
Saw::setSize( cocos2d::Size size )
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
Saw::setAdditionalParam( std::string additionalParam )
{
	int posit = additionalParam.find( ';' );
	_lenth = std::stof( additionalParam.substr( 0, posit ) );
	_time = std::stof( additionalParam.substr( posit + 1, additionalParam.length() - posit - 1 ) );

	_decorator->setAdditionalParam( std::to_string( _time ) );
}

void
Saw::setDirection( Direction direction )
{
	_decorator->setDirection( direction );

	Object::setDirection( direction );
}

void
Saw::hide()
{
	_decorator->hide();

	Object::hide();
}

void
Saw::show()
{
	_decorator->show();

	Object::show();
}

void
Saw::attachToChunk( Chunk & chunk, int zIndex )
{
	_decorator->attachToChunk( chunk, zIndex - 1 );

	Object::attachToChunk( chunk, zIndex );
}

void
Saw::runAction( const std::string & action )
{
	// horizontal init
	cocos2d::Vec2 rightPos = cocos2d::Vec2( getSize().width * _lenth, 0.0f );
	cocos2d::Vec2 leftPos = cocos2d::Vec2( getSize().width * -_lenth, 0.0f );

	auto rotate = cocos2d::RotateBy::create( _time, 360.0f );
	auto goRight = cocos2d::MoveBy::create( _time * 5.0f, rightPos );
	auto goLeft = cocos2d::MoveBy::create( _time * 5.0f, leftPos );

	auto spawnRight = cocos2d::Spawn::create( cocos2d::Repeat::create( rotate, 5 ), goRight, nullptr );
	auto spawnLeft = cocos2d::Spawn::create( cocos2d::Repeat::create( rotate, 5 ), goLeft, nullptr );


	// vertiacal init
	cocos2d::Vec2 upPos = cocos2d::Vec2( 0.0f, getSize().width * _lenth );
	cocos2d::Vec2 downPos = cocos2d::Vec2( 0.0f, getSize().width * -_lenth );

	auto goUp = cocos2d::MoveBy::create( _time * 5.0f, upPos );
	auto goDown = cocos2d::MoveBy::create( _time * 5.0f, downPos );

	auto spawnUp = cocos2d::Spawn::create( cocos2d::Repeat::create( rotate, 5 ), goUp, nullptr );
	auto spawnDown = cocos2d::Spawn::create( cocos2d::Repeat::create( rotate, 5 ), goDown, nullptr );

	// angle init
	float lineLenth = getSize().width * _lenth;

	cocos2d::Action * sequence;

	if( action == "Run" )
	{
		switch ( _direction )
		{
			case Direction::Left:
				sequence = cocos2d::RepeatForever::create( cocos2d::Sequence::create( spawnLeft, spawnRight, nullptr ) );
			break;

			case Direction::Right:
				sequence = cocos2d::RepeatForever::create( cocos2d::Sequence::create( spawnRight, spawnLeft, nullptr ) );
			break;

			case Direction::Top:
				sequence = cocos2d::RepeatForever::create( cocos2d::Sequence::create( spawnUp, spawnDown, nullptr ) );
			break;

			case Direction::Bottom:
				sequence = cocos2d::RepeatForever::create( cocos2d::Sequence::create( spawnDown, spawnUp, nullptr ) );
			break;

			case Direction::D45:
			{
				cocos2d::Vec2 pos1 = cocos2d::Vec2( -lineLenth, lineLenth );
				cocos2d::Vec2 pos2 = cocos2d::Vec2( lineLenth, -lineLenth );

				auto goPos1 = cocos2d::MoveBy::create( _time * 5.0f, pos1 );
				auto goPos2 = cocos2d::MoveBy::create( _time * 5.0f, pos2 );

				auto spawnPos1 = cocos2d::Spawn::create( cocos2d::Repeat::create( rotate, 5 ), goPos1, nullptr );
				auto spawnPos2 = cocos2d::Spawn::create( cocos2d::Repeat::create( rotate, 5 ), goPos2, nullptr );
				sequence = cocos2d::RepeatForever::create( cocos2d::Sequence::create( spawnPos1, spawnPos2, nullptr ) );
			}
			break;

			case Direction::D135:
			{
				cocos2d::Vec2 pos1 = cocos2d::Vec2( lineLenth, lineLenth );
				cocos2d::Vec2 pos2 = cocos2d::Vec2( -lineLenth, -lineLenth );

				auto goPos1 = cocos2d::MoveBy::create( _time * 5.0f, pos1 );
				auto goPos2 = cocos2d::MoveBy::create( _time * 5.0f, pos2 );

				auto spawnPos1 = cocos2d::Spawn::create( cocos2d::Repeat::create( rotate, 5 ), goPos1, nullptr );
				auto spawnPos2 = cocos2d::Spawn::create( cocos2d::Repeat::create( rotate, 5 ), goPos2, nullptr );
				sequence = cocos2d::RepeatForever::create( cocos2d::Sequence::create( spawnPos1, spawnPos2, nullptr ) );
			}
			break;

			case Direction::D225:
			{
				cocos2d::Vec2 pos1 = cocos2d::Vec2( lineLenth, -lineLenth );
				cocos2d::Vec2 pos2 = cocos2d::Vec2( -lineLenth, lineLenth );

				auto goPos1 = cocos2d::MoveBy::create( _time * 5.0f, pos1 );
				auto goPos2 = cocos2d::MoveBy::create( _time * 5.0f, pos2 );

				auto spawnPos1 = cocos2d::Spawn::create( cocos2d::Repeat::create( rotate, 5 ), goPos1, nullptr );
				auto spawnPos2 = cocos2d::Spawn::create( cocos2d::Repeat::create( rotate, 5 ), goPos2, nullptr );
				sequence = cocos2d::RepeatForever::create( cocos2d::Sequence::create( spawnPos1, spawnPos2, nullptr ) );
			}
			break;

			case Direction::D315:
			{
				cocos2d::Vec2 pos1 = cocos2d::Vec2( -lineLenth, -lineLenth );
				cocos2d::Vec2 pos2 = cocos2d::Vec2( lineLenth, lineLenth );

				auto goPos1 = cocos2d::MoveBy::create( _time * 5.0f, pos1 );
				auto goPos2 = cocos2d::MoveBy::create( _time * 5.0f, pos2 );

				auto spawnPos1 = cocos2d::Spawn::create( cocos2d::Repeat::create( rotate, 5 ), goPos1, nullptr );
				auto spawnPos2 = cocos2d::Spawn::create( cocos2d::Repeat::create( rotate, 5 ), goPos2, nullptr );
				sequence = cocos2d::RepeatForever::create( cocos2d::Sequence::create( spawnPos1, spawnPos2, nullptr ) );
			}
			break;

			case Direction::Circle:
			{
				cocos2d::Vec2 center = getPosition();
				center.x += getSize().width * _lenth;
				cocos2d::Vector< cocos2d::FiniteTimeAction * > _rotate;
				auto posit = getPosition();
				for( int i = 0; i < 100; ++i )
				{
					_rotate.pushBack( cocos2d::MoveTo::create( _time / 100, posit ) );
					posit = rotatePoint( posit, center, 3.6f );
				}
				sequence = cocos2d::RepeatForever::create( cocos2d::Sequence::create( _rotate ) );
				_decorator->runAction( "Rotate" );
			}
			default:
			break;
		}

		_sprite->runAction( sequence );
		_audio = Resources::Cache::getInstance().getObjectSound( getName(), "Def" );
	}

	if( action == "Stop" )
	{
		_sprite->stopAllActions();
		_decorator->runAction( "Stop" );
	}
}

cocos2d::Vec2
Saw::rotatePoint( cocos2d::Vec2 point, cocos2d::Vec2 center, float angle ) const
{
    angle = (angle ) * ( M_PI / 180 );
    float rotatedX = cos( angle ) * (point.x - center.x) + sin( angle ) * ( point.y - center.y ) + center.x;
    float rotatedY = -sin( angle ) * ( point.x - center.x ) + cos( angle ) * ( point.y - center.y ) + center.y;
 
    return cocos2d::Vec2( rotatedX, rotatedY );
}

}

}