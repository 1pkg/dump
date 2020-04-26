#include "Gear.hpp"

namespace GameAct
{

namespace Physical
{

std::string
Gear::getName() const
{
	return "Gear";
}

void
Gear::setAdditionalParam( std::string additionalParam )
{
	_time = atof( additionalParam.data() );
}

void
Gear::runAction( const std::string & action )
{
	if( action == "Run" )
	{
		auto rotate = cocos2d::RotateBy::create( _time, 360.0f );
	
		_sprite->runAction( cocos2d::RepeatForever::create( rotate ) );

		return;
	}

	if( action == "Stop" )
	{
		_sprite->stopAllActions();

		return;
	}

	Object::runAction( action );
}

}

}