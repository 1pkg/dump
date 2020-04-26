#include "Barrel.hpp"
#include "Game/Objects/DecorateObject.hpp"
#include "Game.hpp"
#include "Game/Objects/Factories/ObjectsFactory.hpp"

namespace Objects
{

namespace Tech
{

Barrel::Barrel( const std::string & decorator )
	: _decorator( createDecorator( decorator ) )
{
}

void
Barrel::initialize()
{
	StaticObject::initialize();

	cocos2d::PhysicsBody * body = _sprite->getPhysicsBody();
	body->setCategoryBitmask( 0x1 << 3 ); // who ?
	body->setCollisionBitmask( 0x1 << 2 ); // with who ?
	body->setContactTestBitmask( 0x1 << 2 );
}

std::string
Barrel::getName() const
{
	return "Barrel";
}

void
Barrel::setPosition( cocos2d::Vec2 position )
{
	if( _decorator )
		_decorator->setPosition( position );

	StaticObject::setPosition( position );
}

void
Barrel::setSize( cocos2d::Size size )
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
Barrel::hide()
{
	if( _decorator )
		_decorator->hide();

	StaticObject::hide();
}

void
Barrel::show()
{
	if( _decorator )
		_decorator->show();

	StaticObject::show();
}

void
Barrel::attachToChunk( Levels::Chunk & chunk, int zIndex )
{
	if( _decorator )
		_decorator->attachToChunk( chunk, zIndex + 3 );

	StaticObject::attachToChunk( chunk, zIndex );
}

DecorateObject *
Barrel::createDecorator( const std::string & decorator )
{
	Object * obj = Game::getInstance()->getObjectsFactory()->create( decorator );
	DecorateObject * decObj = dynamic_cast< DecorateObject * >( obj );
	return decObj;
}

}

}