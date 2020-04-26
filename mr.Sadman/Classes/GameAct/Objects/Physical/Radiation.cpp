#include "Radiation.hpp"
#include "Game/Levels/Chunk.hpp"

namespace Objects
{

namespace Tech
{

Radiation::Radiation()
	: _particle( cocos2d::ParticleFlower::create() )
{
}

Radiation::~Radiation()
{
	_particle->removeFromParentAndCleanup( true );
}

void
Radiation::initialize()
{
	_particle->setDuration( cocos2d::ParticleSystem::DURATION_INFINITY );
	_particle->setBlendFunc( cocos2d::BlendFunc::ALPHA_NON_PREMULTIPLIED );
	_particle->setPositionType( cocos2d::ParticleSystem::PositionType::RELATIVE );
	_particle->setEmissionRate( 12.0f );
	_particle->setLife( 0.1f );
	_particle->setStartColor( cocos2d::Color4F::GREEN );
	_particle->setEndColor( cocos2d::Color4F::GREEN );

	DecorateObject::initialize();
}

std::string
Radiation::getName() const
{
	return "Radiation";
}

void
Radiation::setPosition( cocos2d::Vec2 position )
{
	_particle->setPosition( position );

	DecorateObject::setPosition( position );
}

void
Radiation::setSize( cocos2d::Size size )
{
	_particle->setEmitterMode( cocos2d::ParticleSystem::Mode::RADIUS );

	float elSize = ( size.width + size.height ) * 0.2f;
	float radSize = ( size.width + size.height ) / 5.0f;
	_particle->setStartSize( elSize );
	_particle->setEndSize( elSize );
	_particle->setStartSizeVar( 0.0f );
	_particle->setEndSizeVar( 0.0f );
	_particle->setStartRadius( radSize );
	_particle->setStartRadiusVar( 0.0f );
	_particle->setEndRadius( radSize * 2.0f );
	_particle->setEndRadiusVar( 0.0f );

	DecorateObject::setSize( size );
}

void
Radiation::hide()
{
	_particle->setVisible( false );

	DecorateObject::hide();
}

void
Radiation::show()
{
	_particle->setVisible( true );

	DecorateObject::show();
}

void
Radiation::attachToChunk( Levels::Chunk & chunk, int zIndex )
{
	chunk.getLayer()->addChild( _particle, zIndex + 1 );

	DecorateObject::attachToChunk( chunk, zIndex );
}

}

}