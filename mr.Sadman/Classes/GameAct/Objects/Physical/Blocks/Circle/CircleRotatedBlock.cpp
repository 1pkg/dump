#include "CircleRotatedBlock.hpp"

namespace GameAct
{

namespace Physical
{

void
CircleRotatedBlock::setAdditionalParam( std::string additionalParam )
{
	std::string time = ThirdParty::readToken( additionalParam );
	_time = atof( time.data() );

	CircleStaticBlock::setAdditionalParam( additionalParam );
}

void
CircleRotatedBlock::runAction( const std::string & action )
{
	if( action == "Rotate" || action == "On" )
	{
		auto action = cocos2d::RepeatForever::create( cocos2d::RotateBy::create( _time, 360.0f ) );
		_representation->runAction( action );

		return;
	}

	if( action == "Stop" || action == "Off" )
	{
		_representation->stopAllActions();

		return;
	}

	Object::runAction( action );
}

}

}