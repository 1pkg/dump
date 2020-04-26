#include "StaticSaw.hpp"
#include "Resources/Cache/Cache.hpp"

namespace GameAct
{

namespace Tech
{

std::string
StaticSaw::getName() const
{
	return "Saw";
}

void
StaticSaw::setAdditionalParam( std::string additionalParam )
{
	_time = std::stof( additionalParam );
}

void
StaticSaw::runAction( const std::string & action )
{
	if( action == "Run" )
	{
		auto rotate = cocos2d::RotateBy::create( _time, 360.0f );
	
		_sprite->runAction( cocos2d::RepeatForever::create( rotate ) );
		_audio = Resources::Cache::getInstance().getObjectSound( getName(), "Def" );
	}

	if( action == "Stop" )
		_sprite->stopAllActions();
}

}

}