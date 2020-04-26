#include "Mine.hpp"
#include "Game.hpp"
#include "Game/Objects/Factories/ObjectsFactory.hpp"
#include "Game/Objects/SubTypes/Stream.hpp"

namespace Objects
{

namespace Tech
{

std::string
Mine::getName() const
{
	return "Mine";
}

void
Mine::runAction( const std::string & action )
{
	if( action == "explosion" )
	{
		hide();

		auto explosion = dynamic_cast< Stream * >( Game::getInstance()->getObjectsFactory()->create( "Explosion" ) );
		explosion->setPosition( getPosition() );
		auto size = getSize();
		size.width *= 6;
		size.height *= 6;
		explosion->setSize( getSize() );

		explosion->showFor( 3.0 );
	}
}

void
Mine::attachToChunk( Levels::Chunk & chunk, int zIndex )
{
	Shell::attachToChunk( chunk, zIndex );

	auto explosion = cocos2d::CallFunc::create( std::bind( &Mine::runAction, this, "explosion" ) );
	auto action = cocos2d::Sequence::create( cocos2d::DelayTime::create( 2.0f ), explosion, nullptr );
	_sprite->runAction( action );
}

}

}