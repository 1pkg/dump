#include "RamPiston.hpp"

namespace GameAct
{

namespace Physical
{

void
RamPiston::initialize()
{
	Object::initialize();

	getBody()->setDynamic( false );
}

std::string
RamPiston::getResourcesName() const
{
	return "RamPiston";
}

void
RamPiston::setPosition( cocos2d::Vec2 position )
{
	_position = position;

	Object::setPosition( position );
}

void
RamPiston::setAdditionalParam( std::string additionalParam )
{
	std::string time = ThirdParty::readToken( additionalParam );
	_time = atof( time.data() );
	std::string delay = ThirdParty::readToken( additionalParam );
	_delay = atof( delay.data() );
	std::string deadly = ThirdParty::readToken( additionalParam );
	if( !deadly.empty() )
		_deadly = atoi( deadly.data() ) == 1;

	Object::setAdditionalParam( additionalParam );
}

void
RamPiston::setRotation( float angle )
{
	_angle = angle;

	Object::setRotation( angle );
}

void
RamPiston::runAction( const std::string & action )
{
	if( action == "Push" || action == "On" )
	{
		float delta = getSize().width;
		float deltaX = delta * sin( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
		float deltaY = delta * cos( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
		cocos2d::Vec2 position( deltaX + _position.x, deltaY + _position.y );

		auto action = cocos2d::MoveTo::create( _time, position );
		_representation->runAction( action );

		return;
	}
	
	if( action == "Pull" || action == "Off"  )
	{
		float delta = getSize().width;
		float deltaX = delta * sin( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
		float deltaY = delta * cos( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
		cocos2d::Vec2 position( -deltaX + _position.x, -deltaY + _position.y );

		auto action = cocos2d::MoveTo::create( _time, position );
		_representation->runAction( action );

		return;
	}

	Object::runAction( action );
	
}

}

}