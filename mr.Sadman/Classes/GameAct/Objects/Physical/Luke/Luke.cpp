#include "Luke.hpp"
#include "Resources/Cache/Cache.hpp"

namespace GameAct
{

namespace Physical
{

void
Luke::initialize()
{
	Object::initialize();

	auto body = cocos2d::PhysicsBody::createBox( _representation->getContentSize() );
	_representation->setPhysicsBody( body );
	body->setDynamic( false );
}

std::string
Luke::getResourcesName() const
{
	return "Luke";
}

void
Luke::runAction( const std::string & action )
{
	if( action == "Open" || action == "On" )
	{
		auto size = getSize();
		setSize( _representation->getContentSize() );
		auto animation = Resources::Cache::getInstance().getObjectAnimation( getResourcesName(), "Open" );
		auto action = cocos2d::Sequence::create(
			animation,
			cocos2d::CallFunc::create( std::bind( &Luke::setOpenBody, this ) ),
			nullptr
		);
		_representation->runAction( action );
		setSize( size );

		return;
	}

	if( action == "Lock" || action == "Off" )
	{
		auto size = getSize();
		setSize( _representation->getContentSize() );
		auto animation = Resources::Cache::getInstance().getObjectAnimation( getResourcesName(), "Lock" );
		auto sequence = cocos2d::Sequence::create(
			animation,
			cocos2d::CallFunc::create( std::bind( &Luke::setLockBody, this ) ),
			nullptr
		);
		_representation->runAction( sequence );
		setSize( size );

		return;
	}

	Object::runAction( action );
}

void
Luke::setOpenBody()
{
	auto size = getSize();
	setSize( _representation->getContentSize() );
	getBody()->removeFromWorld();
	_representation->setPhysicsBody( cocos2d::PhysicsBody::createBox( cocos2d::Size( size.width / 3.0f, size.height ) ) );
	getBody()->setDynamic( false );
	setSize( size );
}

void
Luke::setLockBody()
{
	auto size = getSize();
	setSize( _representation->getContentSize() );
	getBody()->removeFromWorld();
	_representation->setPhysicsBody( cocos2d::PhysicsBody::createBox( size ) );
	getBody()->setDynamic( false );
	setSize( size );
}

}

}