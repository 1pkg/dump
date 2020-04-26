#include "Director.hpp"
#include "GameAct/Act.hpp"
#include "GameAct/Objects/Factories/ObjectsFactory.hpp"
#include "GlueBomb.hpp"
#include "GameAct/Objects/SubTypes/Stream.hpp"

namespace GameAct
{

namespace Physical
{

void
GlueBomb::initialize()
{
	Object::initialize();

	auto body =  cocos2d::PhysicsBody::createBox( getContentSize() );
	_representation->setPhysicsBody( body );
	getBody()->setDynamic( true );
}

std::string
GlueBomb::getResourcesName() const
{
	return "GlueBomb";
}

void
GlueBomb::attachToChunk( Chunk & chunk, int zIndex )
{
	_zindex = zIndex;

	Object::attachToChunk( chunk, zIndex );
}

void
GlueBomb::runAction( const std::string & action )
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