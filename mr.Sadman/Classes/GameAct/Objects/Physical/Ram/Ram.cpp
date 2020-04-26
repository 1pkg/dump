#include "Director.hpp"
#include "GameAct/Act.hpp"
#include "GameAct/Objects/Factories/ObjectsFactory.hpp"
#include "Ram.hpp"

namespace GameAct
{

namespace Physical
{

Ram::Ram()
	: _piston( Director::getInstance().getGameAct()->getObjectsFactory()->create( "RamPiston" ) )
{
}

void
Ram::initialize()
{
	Object::initialize();

	auto body =  cocos2d::PhysicsBody::createBox( _representation->getContentSize() );
	_representation->setPhysicsBody( body );
	body->setDynamic( false );
}

std::string
Ram::getResourcesName() const
{
	return "Ram";
}

void
Ram::setPosition( cocos2d::Vec2 position )
{
	_piston->setPosition( position );

	Object::setPosition( position );
}

void
Ram::setSize( cocos2d::Size size )
{	
	_piston->setSize( size );

	Object::setSize( size );
}

void
Ram::setAdditionalParam( std::string additionalParam )
{
	_piston->setAdditionalParam( additionalParam );
}

void
Ram::setRotation( float angle )
{
	_piston->setRotation( angle );

	Object::setRotation( angle );
}

void
Ram::hide()
{
	_piston->hide();

	Object::hide();
}

void
Ram::show()
{
	_piston->show();

	Object::show();
}

void
Ram::attachToChunk( Chunk & chunk, int zIndex )
{
	_piston->attachToChunk( chunk, zIndex - 1 );

	Object::attachToChunk( chunk, zIndex );
}

void
Ram::runAction( const std::string & action )
{
	if( action == "On" )
	{
		_piston->runAction( "On" );

		return;
	}
	
	if( action == "Off" )
	{
		_piston->runAction( "Off" );

		return;
	}

	Object::runAction( action );
	
}

}

}