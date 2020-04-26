#include "Director.hpp"
#include "GameAct/Act.hpp"
#include "GameAct/Objects/Factories/ObjectsFactory.hpp"
#include "Magnite.hpp"
#include "GameAct/Objects/SubTypes/Stream.hpp"

namespace GameAct
{

namespace Physical
{

Magnite::Magnite()
	: _pivot( Director::getInstance().getGameAct()->getObjectsFactory()->create( "Pivot" ) ),
	_magnetism( dynamic_cast< Stream * >( Director::getInstance().getGameAct()->getObjectsFactory()->create( "Magnetism" ) ) )
{
	_magnetism->hide();
}

void
Magnite::initialize()
{
	Object::initialize();

	getBody()->setDynamic( false );
}

std::string
Magnite::getResourcesName() const
{
	return "Magnite";
}

void
Magnite::setPosition( cocos2d::Vec2 position )
{
	cocos2d::Vec2 pivotPosit = position;
	float delta = _pivot->getSize().width / 2.0f;
	float deltaX = delta * sin( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
	float deltaY = delta * cos( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
	pivotPosit.x += deltaX;
	pivotPosit.y += deltaY;
	_pivot->setPosition( pivotPosit );

	delta = getSize().width * _lenth;
	deltaX = delta * sin( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
	deltaY = delta * cos( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
	position.x += deltaX;
	position.y += deltaY;

	cocos2d::Vec2 magnetismPosition = position;
	delta = getSize().width / 2.0f;
	deltaX = delta * sin( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
	deltaY = delta * cos( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
	magnetismPosition.x += deltaX;
	magnetismPosition.y += deltaY;
	_magnetism->setPosition( magnetismPosition );

	Object::setPosition( position );
}

void
Magnite::setSize( cocos2d::Size size )
{
	cocos2d::Size pivotSize = size;
	pivotSize.width *= _lenth;	
	_pivot->setSize( pivotSize );

	cocos2d::Size magnetismSize = size;
	magnetismSize.width *= _magnetismLenth;		
	_magnetism->setSize( magnetismSize );

	Object::setSize( size );
}

void
Magnite::setAdditionalParam( std::string additionalParam )
{
	std::string lenth = ThirdParty::readToken( additionalParam );
	_lenth = atof( lenth.data() );

	std::string magnetismLenth = ThirdParty::readToken( additionalParam );
	_magnetismLenth = atof( magnetismLenth.data() );

	Object::setAdditionalParam( additionalParam );
}

void
Magnite::setRotation( float angle )
{
	_angle = angle;

	_pivot->setRotation( angle );

	_magnetism->setRotation( angle );

	Object::setRotation( angle );
}

void
Magnite::hide()
{
	_pivot->hide();

	_magnetism->hide();

	Object::hide();
}

void
Magnite::show()
{
	_pivot->show();

	_magnetism->show();

	Object::show();
}

void
Magnite::attachToChunk( Chunk & chunk, int zIndex )
{
	_pivot->attachToChunk( chunk, zIndex - 1 );

	_magnetism->attachToChunk( chunk, zIndex );

	Object::attachToChunk( chunk, zIndex );
}

void
Magnite::runAction( const std::string & action )
{
	if( action == "On" )
	{
		_magnetism->show();

		return;
	}

	if( action == "Off" )
	{
		_magnetism->hide();

		return;
	}

	Object::runAction( action );
}

}

}