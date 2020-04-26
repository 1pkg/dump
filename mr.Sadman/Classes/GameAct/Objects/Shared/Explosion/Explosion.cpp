#include "Explosion.hpp"
#include "Resources/Cache/Cache.hpp"

namespace GameAct
{

namespace Shared
{

void
Explosion::initialize()
{
	Stream::initialize();

	_particle->setStartColor( cocos2d::Color4F::ORANGE );
	_particle->setEndColor( cocos2d::Color4F::RED );
}

std::string
Explosion::getResourcesName() const
{
	return "Explosion";
}

void
Explosion::setSize( cocos2d::Size size )
{
	// configuration
	_particle->setStartSize( 5.0f );
	_particle->setEndSize( 5.0f );
	_particle->setStartSizeVar( 0.0f );
	_particle->setEndSizeVar( 0.0f );
	_particle->setRadialAccel( size.width * size.width / 500.0f );
	_particle->setLife( 0.7f );
	_particle->setLifeVar( 0.2f );
	_particle->setEmissionRate( 80.0f );

	float delta = 2.0f * size.width;
	float x = delta * sin( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
	float y = delta * cos( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
	_particle->setGravity( cocos2d::Vec2( x, y ) );

	Object::setSize( size );
}

}

}