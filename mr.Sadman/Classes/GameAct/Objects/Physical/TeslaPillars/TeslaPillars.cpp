#include "TeslaPillars.hpp"
#include "Resources/Cache/Cache.hpp"

namespace GameAct
{

namespace Physical
{

void
TeslaPillars::initialize()
{
	Object::initialize();

	auto body = Resources::Cache::getInstance().getObjectBody( getResourcesName(), "Blik" );
	_representation->setPhysicsBody( body );
	body->setDynamic( false );

	_audio = Resources::Cache::getInstance().getObjectAudio( getResourcesName(), "Blik" );
	_audio->setLoop( false );
	_audio->pause();
}

std::string
TeslaPillars::getResourcesName() const
{
	return "TeslaPillars";
}

void
TeslaPillars::setAdditionalParam( std::string additionalParam )
{
	std::string time = ThirdParty::readToken( additionalParam );
	_time = atof( time.data() );

	Object::setAdditionalParam( additionalParam );
}

void
TeslaPillars::runAction( const std::string & action )
{
	if( action == "Blik" || action == "On" )
	{
		auto size = getSize();
		setSize( _representation->getContentSize() );
		auto animation = Resources::Cache::getInstance().getObjectAnimation( getResourcesName(), "Blik" );
		auto action = cocos2d::Sequence::create(
			cocos2d::CallFunc::create( std::bind( &TeslaPillars::setBlickBody, this ) ),
			animation,
			cocos2d::CallFunc::create( std::bind( &TeslaPillars::setDefBody, this ) ),
			cocos2d::DelayTime::create( _time ),
			nullptr
		);
		_representation->runAction( cocos2d::RepeatForever::create( action ) );

		_audio->resume();

		return;
	}

	if( action == "Off" )
	{
		_representation->stopAllActions();

		_audio->pause();

		return;
	}
	Object::runAction( action );
}

void
TeslaPillars::setBlickBody()
{
	auto size = getSize();
	setSize( _representation->getContentSize() );
	getBody()->removeFromWorld();
	_representation->setPhysicsBody( Resources::Cache::getInstance().getObjectBody( getResourcesName(), "Blik" ) );
	getBody()->setDynamic( false );
	setSize( size );
	getBody()->removeFromWorld();
}

void
TeslaPillars::setDefBody()
{
	auto size = getSize();
	setSize( _representation->getContentSize() );
	getBody()->removeFromWorld();
	_representation->setPhysicsBody( Resources::Cache::getInstance().getObjectBody( getResourcesName() ) );
	getBody()->setDynamic( false );
	setSize( size );
	getBody()->removeFromWorld();
}

}

}