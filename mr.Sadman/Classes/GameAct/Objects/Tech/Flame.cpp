#include "Flame.hpp"
#include "Game/Levels/Chunk.hpp"

namespace Objects
{

namespace Tech
{

Flame::Flame( Direction direction )
	: _particle( cocos2d::ParticleMeteor::create() ),
	_direction( direction )
{
}

Flame::~Flame()
{
	_particle->removeFromParentAndCleanup( true );
}

void
Flame::initialize()
{
	_sprite = cocos2d::Sprite::create();
	_sprite->setContentSize( cocos2d::Size( 64.0f, 64.0f ) );
	auto body = cocos2d::PhysicsBody::createBox( _sprite->getContentSize() );
	_sprite->setPhysicsBody( body );

	body->setDynamic( false );
	body->setCategoryBitmask( 0x1 ); // who ?
	body->setCollisionBitmask( 0x1 << 1 ); // with who ?

	setRotation( +_direction );

	_particle->setDuration( cocos2d::ParticleSystem::DURATION_INFINITY );
	_particle->setBlendFunc( cocos2d::BlendFunc::ALPHA_NON_PREMULTIPLIED );
	_particle->setPositionType( cocos2d::ParticleSystem::PositionType::RELATIVE );
	_particle->setEmissionRate( 200.0f );
	_particle->setLife( 0.4f );
	_particle->setLifeVar( 0.0f );
	_particle->setStartColor( cocos2d::Color4F::ORANGE );
	_particle->setEndColor( cocos2d::Color4F::RED );
}

std::string
Flame::getName() const
{
	return "Flame";
}

void
Flame::setPosition( cocos2d::Vec2 position )
{
	cocos2d::Vec2 myPosition = position;
	switch ( _direction )
	{
		case Objects::Direction::Right:
			myPosition.x += getSize().width / 2.0f;
		break;

		case Objects::Direction::Left:
			myPosition.x -= getSize().width / 2.0f;
		break;

		case Objects::Direction::Top:
			myPosition.y += getSize().width / 2.0f;
		break;

		case Objects::Direction::Bottom:
			myPosition.y -= getSize().width / 2.0f;
		break;

		default:
		break;
	}

	_particle->setPosition( position );

	StaticObject::setPosition( myPosition );
}

void
Flame::setSize( cocos2d::Size size )
{
	float bulSize = ( size.width + size.height ) * 0.025f;
	_particle->setStartSize( bulSize );
	_particle->setEndSize( bulSize );
	_particle->setStartSizeVar( 0.0f );
	_particle->setEndSizeVar( 0.0f );

	switch ( _direction )
	{
		case Objects::Direction::Right:
			_particle->setGravity( cocos2d::Vec2( size.width * 3.0f, 0.0f ) );
		break;

		case Objects::Direction::Left:
			_particle->setGravity( cocos2d::Vec2( size.width * -3.0f, 0.0f ) );
		break;

		case Objects::Direction::Top:
			_particle->setGravity( cocos2d::Vec2( 0.0f, size.height * 3.0f ) );
		break;

		case Objects::Direction::Bottom:
			_particle->setGravity( cocos2d::Vec2( 0.0f, size.height * -3.0f ) );
		break;

		default:
		break;
	}

	StaticObject::setSize( size );
}

void
Flame::hide()
{
	_particle->setVisible( false );

	StaticObject::hide();
}

void
Flame::show()
{
	_particle->setVisible( true );

	StaticObject::show();
}

void
Flame::attachToChunk( Levels::Chunk & chunk, int zIndex )
{
	chunk.getLayer()->addChild( _particle, zIndex + 2 );

	StaticObject::attachToChunk( chunk, zIndex );
}

}

}