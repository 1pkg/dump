#include "Stream.hpp"
#include "GameAct/Levels/Chunk.hpp"

namespace GameAct
{

Stream::~Stream()
{
	_particle->removeFromParentAndCleanup( true );
}

void
Stream::initialize()
{
	Area::initialize();

	_audio->setLoop( true );

	_particle = cocos2d::ParticleMeteor::create();
	_particle->setDuration( cocos2d::ParticleSystem::DURATION_INFINITY );
	_particle->setBlendFunc( cocos2d::BlendFunc::ALPHA_NON_PREMULTIPLIED );
	_particle->setPositionType( cocos2d::ParticleSystem::PositionType::RELATIVE );

	auto body = getBody();

	body->setCategoryBitmask( 0x1 );
	body->setCollisionBitmask( 0x1 );
	body->setContactTestBitmask( 0x1 );

}

void
Stream::setPosition( cocos2d::Vec2 position )
{
	_particle->setPosition( position );

	float delta = getSize().width / 2.0f;
	float deltaX = delta * sin( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
	float deltaY = delta * cos( CC_DEGREES_TO_RADIANS( _angle  + 90.0f ) );
	position.x += deltaX;
	position.y += deltaY;
	Area::setPosition( position );
}

void
Stream::setRotation( float angle )
{
	_angle = angle;

	Area::setRotation( angle );
}

void
Stream::hide()
{
	_particle->setVisible( false );

	if( _audio )
		_audio->pause();

	Object::hide();
}

void
Stream::show()
{
	if( _audio )
		_audio->resume();

	_particle->setVisible( true );

	Object::show();
}

void
Stream::showFor( float duration )
{
	auto show = cocos2d::CallFunc::create( std::bind( &Stream::show, this ) );
	auto hide = cocos2d::CallFunc::create( std::bind( &Stream::hide, this ) );
	auto action = cocos2d::Sequence::create( show, cocos2d::DelayTime::create( duration ), hide, nullptr);
	_representation->runAction( action );
}

void
Stream::attachToChunk( Chunk & chunk, int zIndex )
{
	chunk.getLayer()->addChild( _particle, zIndex + 2 );

	Area::attachToChunk( chunk, zIndex );
}

}