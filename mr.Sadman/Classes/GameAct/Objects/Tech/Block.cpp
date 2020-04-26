#include "Block.hpp"
#include "Game/Objects/DecorateObject.hpp"
#include "Game.hpp"
#include "Game/Cache/GameCache.hpp"
#include "Game/Objects/Factories/ObjectsFactory.hpp"
#include "Ball.hpp"

namespace Objects
{

namespace Tech
{

void
Block::interact( Ball * ball )
{
	hide();
	ball->hide();
}

Block::Block( const std::string & decorator )
	: _decorator( createDecorator( decorator ) )
{
}

void
Block::initialize()
{
	_sprite = Game::getInstance()->getGameCache()->getObjectSprite( getName() );

	cocos2d::PhysicsBody * body = cocos2d::PhysicsBody::createBox( _sprite->getContentSize() );	
	_sprite->setPhysicsBody( body );

	body->setDynamic( false );

	body->setCategoryBitmask( 0x1 << 3 ); // who ?
	body->setCollisionBitmask( 0x1 << 2 ); // with who ?
	body->setContactTestBitmask( 0x1 << 2 );
}

std::string
Block::getName() const
{
	return "Block";
}

void
Block::setPosition( cocos2d::Vec2 position )
{
	if( _decorator )
		_decorator->setPosition( position );

	StaticObject::setPosition( position );
}

void
Block::setSize( cocos2d::Size size )
{
	if( _decorator )
	{
		cocos2d::Size decSize = size;
		decSize.width /= 2.0; 
		decSize.height /= 2.0;
		_decorator->setSize( decSize );
	}

	StaticObject::setSize( size );
}

void
Block::hide()
{
	if( _decorator )
		_decorator->hide();

	StaticObject::hide();
}

void
Block::show()
{
	if( _decorator )
		_decorator->show();

	StaticObject::show();
}

void
Block::attachToChunk( Levels::Chunk & chunk, int zIndex )
{
	if( _decorator )
		_decorator->attachToChunk( chunk, zIndex + 3 );

	StaticObject::attachToChunk( chunk, zIndex );
}

void
Block::runInteraction( Object * object )
{
	object->interact( this );
}

DecorateObject *
Block::createDecorator( const std::string & decorator )
{
	Object * obj =  Game::getInstance()->getObjectsFactory()->create( decorator );
	DecorateObject * decObj = dynamic_cast< DecorateObject * >( obj );
	return decObj;
}

}

}