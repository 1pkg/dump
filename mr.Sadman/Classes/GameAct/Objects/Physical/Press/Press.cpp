#include "Director.hpp"
#include "GameAct/Act.hpp"
#include "GameAct/Objects/Factories/ObjectsFactory.hpp"
#include "Press.hpp"

namespace GameAct
{

namespace Physical
{

Press::Press()
	: _ram( Director::getInstance().getGameAct()->getObjectsFactory()->create( "Ram" ) )
	, _pushPlate( Director::getInstance().getGameAct()->getObjectsFactory()->create( "PushPlate" ) )
{
	_pushPlate->addSlave( _ram );

	_objects.push_back( _ram );
	_objects.push_back( _pushPlate );
}

std::string
Press::getResourcesName() const
{
	return "Press";
}

void
Press::setPosition( cocos2d::Vec2 position )
{
	_ram->setPosition( position );

	auto pushPlateposition = position;
	float delta = _ram->getSize().width;
	float deltaX = delta * sin( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
	float deltaY = delta * cos( CC_DEGREES_TO_RADIANS( _angle + 90.0f ) );
	pushPlateposition.x -= deltaX;
	pushPlateposition.y -= deltaY;
	_pushPlate->setPosition( pushPlateposition );
}

void
Press::setSize( cocos2d::Size size )
{	
	_ram->setSize( size );

	auto pushPlateSize = size;
	pushPlateSize.height /= 4.0f;
	pushPlateSize.width /= 4.0f;
	_pushPlate->setSize( pushPlateSize );
}

void
Press::setAdditionalParam( std::string additionalParam )
{
	_ram->setAdditionalParam( additionalParam + ";1" );
}

void
Press::setRotation( float angle )
{
	_angle = angle;

	_ram->setRotation( angle );

	_pushPlate->setRotation( angle );
}

void
Press::hide()
{
	_ram->hide();

	_pushPlate->hide();
}

void
Press::show()
{
	_ram->show();

	_pushPlate->show();
}

void
Press::attachToChunk( Chunk & chunk, int zIndex )
{
	_ram->attachToChunk( chunk, zIndex );

	_pushPlate->attachToChunk( chunk, zIndex );
}

}

}