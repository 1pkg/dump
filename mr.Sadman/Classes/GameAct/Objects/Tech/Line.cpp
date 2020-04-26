#include "Line.hpp"
#include "Resources/Cache/Cache.hpp"

namespace GameAct
{

namespace Tech
{

void
Line::initialize()
{
	_sprite = Resources::Cache::getInstance().getObjectSprite( getName() );
}

std::string
Line::getName() const
{
	return "Line";
}

void
Line::setAdditionalParam( std::string additionalParam )
{
	_rotationTime = std::stof( additionalParam );
}

void
Line::runAction( const std::string & action )
{
	if( action == "Rotate" )
	{
		_sprite->setAnchorPoint( cocos2d::Vec2( 1.0f, 0.5f ) );
		_sprite->runAction( cocos2d::RepeatForever::create( cocos2d::RotateBy::create( _rotationTime, 360.0f ) ) );
	}

	if( action == "Stop" )
		_sprite->stopAllActions();
}

}

}