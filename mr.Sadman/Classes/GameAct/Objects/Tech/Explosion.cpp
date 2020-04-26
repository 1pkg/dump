#include "Explosion.hpp"
#include "Game/Levels/Chunk.hpp"

namespace Objects
{

namespace Tech
{

Explosion::Explosion()
	: Stream( Direction::Empty )
{
}

void
Explosion::initialize()
{
	Stream::initialize();

	_particle->setStartColor( cocos2d::Color4F::RED );
	_particle->setEndColor( cocos2d::Color4F::ORANGE );
}

std::string
Explosion::getName() const
{
	return "Explosion";
}

void
Explosion::setSize( cocos2d::Size size )
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
		case Objects::Direction::Left:
			_particle->setGravity( cocos2d::Vec2( -2.0f * size.width, 0.0f ) );
		break;

		case Objects::Direction::Right:
			_particle->setGravity( cocos2d::Vec2( 2.0f * size.width, 0.0f ) );
		break;

		case Objects::Direction::Top:
			_particle->setGravity( cocos2d::Vec2( 0.0f, 2.0f * size.width ) );
		break;

		case Objects::Direction::Bottom:
			_particle->setGravity( cocos2d::Vec2( 0.0f, -2.0f * size.width ) );
		break;

		case Objects::Direction::D45:
			_particle->setGravity( cocos2d::Vec2( -2.0f * size.width * koef, 2.0f * size.width * koef ) );
		break;

		case Objects::Direction::D135:
			_particle->setGravity( cocos2d::Vec2( 2.0f * size.width * koef, 2.0f * size.width * koef ) );
		break;

		case Objects::Direction::D225:
			_particle->setGravity( cocos2d::Vec2( 2.0f * size.width * koef, -2.0f * size.width * koef ) );
		break;

		case Objects::Direction::D315:
			_particle->setGravity( cocos2d::Vec2( -2.0f * size.width * koef, -2.0f * size.width * koef ) );
		break;

		default:
		break;
	}

	StaticObject::setSize( size );
}

}

}