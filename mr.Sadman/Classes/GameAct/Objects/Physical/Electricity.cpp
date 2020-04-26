#include "Electricity.hpp"
#include "Game/Levels/Chunk.hpp"

namespace Objects
{

namespace Tech
{

Electricity::Electricity()
	: _particle( cocos2d::ParticleFlower::create() )
{
	_particle->setEmitterMode( cocos2d::ParticleSystem::Mode::RADIUS );
}


Electricity::~Electricity()
{
	_particle->removeFromParentAndCleanup( true );
}

void
Electricity::initialize()
{
	_particle->setDuration( cocos2d::ParticleSystem::DURATION_INFINITY );
	_particle->setBlendFunc( cocos2d::BlendFunc::ALPHA_NON_PREMULTIPLIED );
	_particle->setPositionType( cocos2d::ParticleSystem::PositionType::RELATIVE );
	_particle->setEmissionRate( 2.0f );
	_particle->setLife( 0.1f );
	_particle->setStartColor( cocos2d::Color4F::YELLOW );
	_particle->setEndColor( cocos2d::Color4F::YELLOW );

	DecorateObject::initialize();
}

std::string
Electricity::getName() const
{
	return "Electricity";
}

void
Electricity::setPosition( cocos2d::Vec2 position )
{
	_particle->setPosition( position );

	DecorateObject::setPosition( position );
}

void
Electricity::setSize( cocos2d::Size size )
{
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
Electricity::hide()
{
	_particle->setVisible( false );

	DecorateObject::hide();
}

void
Electricity::show()
{
	_particle->setVisible( true );

	DecorateObject::show();
}

void
Electricity::attachToChunk( Levels::Chunk & chunk, int zIndex )
{
	chunk.getLayer()->addChild( _particle, zIndex + 1 );

	DecorateObject::attachToChunk( chunk, zIndex );
}

}

}