#include "Director.hpp"
#include "GameAct/Act.hpp"
#include "GameAct/Objects/Factories/ObjectsFactory.hpp"
#include "Generator.hpp"
#include "GameAct/Objects/SubTypes/Stream.hpp"
#include "Resources/Cache/Cache.hpp"


namespace GameAct
{

namespace Physical
{

Generator::Generator( )
	: _electricity( dynamic_cast< Stream * >( Director::getInstance().getGameAct()->getObjectsFactory()->create( "Electricity" ) ) )
{
	_electricity->hide();
}

void
Generator::initialize()
{
	Object::initialize();

	getBody()->setDynamic( false );
}

std::string
Generator::getResourcesName() const
{
	return "Generator";
}

void
Generator::setPosition( cocos2d::Vec2 position )
{
	cocos2d::Vec2 elPosition = position;
	float delta = getSize().height / 2.0f;
	float deltaX = delta * sin( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
	float deltaY = delta * cos( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
	elPosition.x += deltaX;
	elPosition.y += deltaY;
	_electricity->setPosition( elPosition );

	Object::setPosition( position );
}

void
Generator::setSize( cocos2d::Size size )
{
	cocos2d::Size elSize = size;
	elSize.width *= 2.0f;
	elSize.height *= 3.0f;		
	_electricity->setSize( elSize );

	Object::setSize( size );
}

void
Generator::setAdditionalParam( std::string additionalParam )
{
	std::string time = ThirdParty::readToken( additionalParam );
	_time = atof( time.data() );

	Object::setAdditionalParam( additionalParam );
}

void
Generator::setRotation( float angle )
{
	_angle = angle;

	Object::setRotation( angle );
}

void
Generator::show()
{
	_electricity->show();

	Object::show();
}

void
Generator::hide()
{
	_electricity->hide();

	Object::hide();
}

void
Generator::attachToChunk( Chunk & chunk, int zIndex )
{
	_electricity->attachToChunk( chunk, zIndex );

	Object::attachToChunk( chunk, zIndex );
}

void
Generator::runAction( const std::string & action )
{
	if( action == "Blik" || action == "On" )
	{
		auto size = getSize();
		setSize( _representation->getContentSize() );
		auto animation = Resources::Cache::getInstance().getObjectAnimation( getResourcesName(), "Blik" );
		auto blik = [ this ]()
		{
			_electricity->showFor( _time / 2.0f );
		};
		auto action = cocos2d::Sequence::create( animation, cocos2d::CallFunc::create( blik ), cocos2d::DelayTime::create( _time ), nullptr );
		_representation->runAction( cocos2d::RepeatForever::create( action ) );
		setSize( size );

		return;
	}

	if( action == "Off" )
	{
		_representation->stopAllActions();

		return;
	}

	Object::runAction( action );
}

}

}