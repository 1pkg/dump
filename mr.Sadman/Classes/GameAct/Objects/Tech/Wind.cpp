#include "Wind.hpp"

namespace GameAct
{

namespace Tech
{

void
Wind::initialize()
{
	Stream::initialize();

	_particle->setStartColor( cocos2d::Color4F::WHITE );
	_particle->setEndColor( cocos2d::Color4F::WHITE );
}

std::string
Wind::getName() const
{
	return "Wind";
}

void
Wind::setSize( cocos2d::Size size )
{
	// configuration
	float koef = 1.0f / sqrt( 2.0f );
	_particle->setStartSize( 5.0f );
	_particle->setEndSize( 5.0f );
	_particle->setStartSizeVar( 0.0f );
	_particle->setEndSizeVar( 0.0f );
	_particle->setRadialAccel( size.width * size.width / 500.0f );
	_particle->setLife( 0.7f );
	_particle->setLifeVar( 0.2f );
	_particle->setEmissionRate( 80.0f );

	switch ( _direction )
	{
		case Direction::Left:
			_particle->setGravity( cocos2d::Vec2( -2.0f * size.width, 0.0f ) );
		break;

		case Direction::Right:
			_particle->setGravity( cocos2d::Vec2( 2.0f * size.width, 0.0f ) );
		break;

		case Direction::Top:
			_particle->setGravity( cocos2d::Vec2( 0.0f, 2.0f * size.width ) );
		break;

		case Direction::Bottom:
			_particle->setGravity( cocos2d::Vec2( 0.0f, -2.0f * size.width ) );
		break;

		case Direction::D45:
			_particle->setGravity( cocos2d::Vec2( -2.0f * size.width * koef, 2.0f * size.width * koef ) );
		break;

		case Direction::D135:
			_particle->setGravity( cocos2d::Vec2( 2.0f * size.width * koef, 2.0f * size.width * koef ) );
		break;

		case Direction::D225:
			_particle->setGravity( cocos2d::Vec2( 2.0f * size.width * koef, -2.0f * size.width * koef ) );
		break;

		case Direction::D315:
			_particle->setGravity( cocos2d::Vec2( -2.0f * size.width * koef, -2.0f * size.width * koef ) );
		break;

		default:
		break;
	}

	Object::setSize( size );
}

}

}