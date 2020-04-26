#include "CannonOneOff.hpp"
#include "Game.hpp"
#include "Game/Objects/Factories/ObjectsFactory.hpp"
#include "Game/Events/EventHandler.hpp"

namespace Objects
{

namespace Tech
{

void
CannonOneOff::handleEvent( Events::CannonEvent * ev )
{
	runAction( "fire" );
}

CannonOneOff::CannonOneOff( Direction direction, const std::string & shell )
	: _shell( shell ),
	_used( false ),
	_direction( direction )
{
}

void
CannonOneOff::initialize()
{
	DynamicObject::initialize();

	switch ( _direction )
	{
		case Objects::Direction::Left:
			setRotation( 180.0f );
		break;

		case Objects::Direction::Top:
			setRotation( -90.0f );
		break;

		case Objects::Direction::Bottom:
			setRotation( 90.0f );
		break;

		default:
		break;
	}

	Events::EventHandler::subscribe( "CannonEvent", this );
}

std::string
CannonOneOff::getName() const
{
	return "CannonOneOff";
}

void
CannonOneOff::setRotation( float angle )
{
	if( angle == 180.0f )
	{
		_sprite->runAction( cocos2d::ScaleBy::create( 0.0f, -1.0f, 1.0f ) );
		return;
	}

	DynamicObject::setRotation( angle );
}

void
CannonOneOff::runAction( const std::string & action )
{
	if( action == "fire" && !_used )
	{
		onFire();
		_used = true;

		return;
	}

	DynamicObject::runAction( action );
}

void
CannonOneOff::onFire()
{
	DynamicObject * shell = createShell( _shell );

	cocos2d::Size shellSize = getSize();
	shellSize.width /= 6.0f;
	shellSize.height /= 6.0f;
	shell->setSize( shellSize );

	cocos2d::Vec2 shellPosition = getPosition();
	switch ( _direction )
	{
		case Objects::Direction::Left:
			shellPosition.x -= getSize().width / 2.2f;
			shellPosition.y += getSize().height / 3.0f;
		break;

		case Objects::Direction::Right:
			shellPosition.x += getSize().width / 2.2f;
			shellPosition.y += getSize().height / 3.0f;
		break;

		case Objects::Direction::Top:
			shellPosition.x += getSize().width / 3.0f;
			shellPosition.y += getSize().height / 2.2f;
		break;

		case Objects::Direction::Bottom:
			shellPosition.x += getSize().width / 3.0f;
			shellPosition.y -= getSize().height / 2.2f;
		break;

		default:
		break;
	}
	shell->setPosition( shellPosition );
		
	shell->attachToChunk( *_chunk, 0 );

	cocos2d::Size mySize = getSize();
	switch ( _direction )
	{
		case Objects::Direction::Left:
			shell->getBody()->applyImpulse( cocos2d::Vec2( -3000.0f * shellSize.width, -50.0f * shellSize.height ) );
			getBody()->applyImpulse( cocos2d::Vec2( 30.0f * mySize.width, 0.0f ) );
		break;

		case Objects::Direction::Right:
			shell->getBody()->applyImpulse( cocos2d::Vec2( 3000.0f * shellSize.width, -50.0f * shellSize.height ) );
			getBody()->applyImpulse( cocos2d::Vec2( -30.0f * mySize.width, 0.0f ) );
		break;

		case Objects::Direction::Top:
			shell->getBody()->applyImpulse( cocos2d::Vec2( 0.0f, 3000.0f * shellSize.height ) );
			getBody()->applyImpulse( cocos2d::Vec2( 0.0f, -30.0f * shellSize.height ) );
		break;

		case Objects::Direction::Bottom:
			shell->getBody()->applyImpulse( cocos2d::Vec2( 0.0f, -3000.0f * shellSize.height ) );
			getBody()->applyImpulse( cocos2d::Vec2( 0.0f, 30.0f * shellSize.height ) );
		break;

		default:
		break;
	}

	shell->getBody()->setLinearDamping( 0.5f );
	getBody()->setLinearDamping( 0.9f );
}

DynamicObject *
CannonOneOff::createShell( const std::string & shell )
{
	Object * obj = Game::getInstance()->getObjectsFactory()->create( shell );
	DynamicObject * dynObj = dynamic_cast< DynamicObject * >( obj );
	return dynObj;
}

}

}