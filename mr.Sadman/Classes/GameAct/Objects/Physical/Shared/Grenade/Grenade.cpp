#include "Director.hpp"
#include "GameAct/Act.hpp"
#include "GameAct/Objects/Factories/ObjectsFactory.hpp"
#include "Grenade.hpp"
#include "GameAct/Objects/SubTypes/Stream.hpp"

namespace GameAct
{

namespace Physical
{

void
Grenade::initialize()
{
	Object::initialize();

	auto body =  cocos2d::PhysicsBody::createBox( getContentSize() );
	_representation->setPhysicsBody( body );
	getBody()->setDynamic( true );
}

std::string
Grenade::getResourcesName() const
{
	return "Grenade";
}

void
Grenade::attachToChunk( Chunk & chunk, int zIndex )
{
	_zindex = zIndex;

	Object::attachToChunk( chunk, zIndex );
}

void
Grenade::runAction( const std::string & action )
{
	if( action == "Explode" )
	{
		hide();

		auto explosion = dynamic_cast< Stream * >( Director::getInstance().getGameAct()->getObjectsFactory()->create( "Explosion" ) );
		explosion->setPosition( getPosition() );
		auto size = getSize();
		size.width *= 8.0f;
		size.height *= 8.0f;
		explosion->setSize( size );
		explosion->attachToChunk( *_chunk, _zindex );
		explosion->showFor( 1.5f );

		return;
	}

	Object::runAction( action );
}

}

}