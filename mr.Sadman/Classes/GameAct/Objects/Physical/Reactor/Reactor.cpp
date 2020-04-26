#include "Director.hpp"
#include "GameAct/Act.hpp"
#include "GameAct/Objects/Factories/ObjectsFactory.hpp"
#include "Reactor.hpp"
#include "GameAct/Objects/SubTypes/Stream.hpp"

namespace GameAct
{

namespace Physical
{

Reactor::Reactor()
	: _radiation( dynamic_cast< Stream * >( Director::getInstance().getGameAct()->getObjectsFactory()->create( "Radiation" ) ) )
{
}

void
Reactor::initialize()
{
	Object::initialize();

	auto body =  cocos2d::PhysicsBody::createBox( _representation->getContentSize() );
	_representation->setPhysicsBody( body );
	body->setDynamic( false );
}

std::string
Reactor::getResourcesName() const
{
	return "Reactor";
}

void
Reactor::setPosition( cocos2d::Vec2 position )
{
	_radiation->setPosition( position );

	Object::setPosition( position );
}

void
Reactor::setSize( cocos2d::Size size )
{
	cocos2d::Size radiationSize = size;
	radiationSize.width *= _radiationLenth;
	radiationSize.height *= _radiationLenth;		
	_radiation->setSize( radiationSize );

	Object::setSize( size );
}

void
Reactor::setAdditionalParam( std::string additionalParam )
{
	std::string radiationLenth = ThirdParty::readToken( additionalParam );
	_radiationLenth = atof( radiationLenth.data() );

	Object::setAdditionalParam( additionalParam );
}

void
Reactor::setRotation( float angle )
{
	_angle = angle;

	_radiation->setRotation( angle );

	Object::setRotation( angle );
}

void
Reactor::hide()
{
	_radiation->hide();

	Object::hide();
}

void
Reactor::show()
{
	_radiation->show();

	Object::show();
}

void
Reactor::attachToChunk( Chunk & chunk, int zIndex )
{
	_zindex = zIndex;

	_radiation->attachToChunk( chunk, zIndex );

	Object::attachToChunk( chunk, zIndex );
}

void
Reactor::runAction( const std::string & action )
{
	if( action == "Explode" || action == "Off" )
	{
		hide();

		auto explosion = dynamic_cast< Stream * >( Director::getInstance().getGameAct()->getObjectsFactory()->create( "Explosion" ) );
		explosion->setPosition( getPosition() );
		auto size = _radiation->getSize();
		size.width *= 3.0f;
		size.height *= 3.0f;
		explosion->setSize( size );
		explosion->attachToChunk( *_chunk, _zindex );

		explosion->showFor( 1.5f );

		return;
	}

	Object::runAction( action );
}

}

}