#include "StaticSaw.hpp"
#include "Resources/Cache/Cache.hpp"

namespace GameAct
{

namespace Physical
{

void
StaticSaw::initialize()
{
	Object::initialize();

	auto body =  cocos2d::PhysicsBody::createBox( _representation->getContentSize() );
	_representation->setPhysicsBody( body );
	body->setDynamic( false );

	_audio = Resources::Cache::getInstance().getObjectAudio( getResourcesName(), "Rotate" );
	_audio->setLoop( true );
	_audio->pause();
}

std::string
StaticSaw::getResourcesName() const
{
	return "Saw";
}

void
StaticSaw::setAdditionalParam( std::string additionalParam )
{
	std::string time = ThirdParty::readToken( additionalParam );
	_time = atof( time.data() );

	Object::setAdditionalParam( additionalParam );
}

void
StaticSaw::runAction( const std::string & action )
{
	if( action == "On" )
	{
		auto action = cocos2d::RotateBy::create( _time, 360.0f );
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

}

}