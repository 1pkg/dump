#include "Director.hpp"
#include "GameAct/Act.hpp"
#include "GameAct/Objects/Factories/ObjectsFactory.hpp"
#include "Cannon.hpp"
#include "GameAct/Objects/SubTypes/Shell.hpp"
#include "Resources/Cache/Cache.hpp"

namespace GameAct
{

namespace Tech
{


std::string
Cannon::getName() const
{
	return "Cannon";
}

void
Cannon::setAdditionalParam( std::string additionalParam )
{
	_shell = additionalParam;
}

void
Cannon::setDirection( Direction direction )
{
	_direction = direction;
}

void
Cannon::setRotation( float angle )
{
	if( angle == 0.0f )
	{
		_sprite->runAction( cocos2d::ScaleBy::create( 0.0f, -1.0f, 1.0f ) );
		return;
	}
}

void
Cannon::attachToChunk( Chunk & chunk, int zIndex )
{
	_zIndex = zIndex;

	setRotation( toDegree( _direction ) );

	Object::attachToChunk( chunk, zIndex );
}

void
Cannon::runAction( const std::string & action )
{
	if( action == "EndlessFire" )
	{
		auto size = getSize();
		setSize( _sprite->getContentSize() );

		auto fire = Resources::Cache::getInstance().getObjectAnimation( getName(), "Fire" );
		//auto back = Resources::Cache::getInstance().getObjectAnimation( getName(), "Back" );

		auto sequence = cocos2d::RepeatForever::create( cocos2d::Sequence::create( fire, cocos2d::CallFunc::create( std::bind( &Cannon::onFire, this ) ), nullptr ) );
		_sprite->runAction( sequence );
		setSize( size );

		return;
	}

	if( action == "Fire" )
	{
		auto size = getSize();
		setSize( _sprite->getContentSize() );

		auto fire = Resources::Cache::getInstance().getObjectAnimation( getName(), "Fire" );
		auto back = Resources::Cache::getInstance().getObjectAnimation( getName(), "Back" );

		auto sequence = cocos2d::Sequence::create( fire, cocos2d::CallFunc::create( std::bind( &Cannon::onFire, this ) ), back, nullptr );
		_sprite->runAction( sequence );
		setSize( size );

		return;
	}
	
	if( action == "Stop" )
	{
		_sprite->stopAllActions();

		return;
	}

	Object::runAction( action );
}

void
Cannon::onFire()
{
	Object * shell = createShell( _shell );

	cocos2d::Size shellSize = getSize();
	shellSize.width /= 6.0f;
	shellSize.height /= 6.0f;
	shell->setSize( shellSize );

	cocos2d::Vec2 shellPosition = getPosition();
	switch ( _direction )
	{
		case Direction::Left:
			shellPosition.x -= getSize().width / 2.2f;
			shellPosition.y += getSize().height / 3.0f;
		break;

		case Direction::Right:
			shellPosition.x += getSize().width / 2.2f;
			shellPosition.y += getSize().height / 3.0f;
		break;

		case Direction::Top:
			shellPosition.x += getSize().width / 3.0f;
			shellPosition.y += getSize().height / 2.2f;
		break;

		case Direction::Bottom:
			shellPosition.x += getSize().width / 3.0f;
			shellPosition.y -= getSize().height / 2.2f;
		break;

		default:
		break;
	}
	shell->setPosition( shellPosition );
		
	shell->attachToChunk( *_chunk, _zIndex + 1 );

	cocos2d::Size mySize = getSize();
	switch ( _direction )
	{
		case Direction::Left:
			shell->getBody()->applyImpulse( cocos2d::Vec2( -3000.0f * shellSize.width, -50.0f * shellSize.height ) );
		break;

		case Direction::Right:
			shell->getBody()->applyImpulse( cocos2d::Vec2( 3000.0f * shellSize.width, -50.0f * shellSize.height ) );
		break;

		case Direction::Top:
			shell->getBody()->applyImpulse( cocos2d::Vec2( 0.0f, 3000.0f * shellSize.height ) );
		break;

		case Direction::Bottom:
			shell->getBody()->applyImpulse( cocos2d::Vec2( 0.0f, -3000.0f * shellSize.height ) );
		break;

		default:
		break;
	}

	shell->getBody()->setLinearDamping( 0.5f );
}

Shell *
Cannon::createShell( const std::string & shell )
{
	Object * obj = Director::getInstance().getGameAct()->getObjectsFactory()->create( shell );
	Shell * shellO = dynamic_cast< Shell * >( obj );
	return shellO;
}

}

}