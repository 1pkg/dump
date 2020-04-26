#include "CompositeLongObject.hpp"

namespace GameAct
{

void
CompositeLongObject::initialize()
{
	_representation = nullptr;
	_audio = nullptr;
}

cocos2d::Size
CompositeLongObject::getSize() const
{
	return getHip()->getSize();
}

cocos2d::Size
CompositeLongObject::getContentSize() const
{
	return getHip()->getContentSize();
}

cocos2d::Vec2
CompositeLongObject::getPosition() const
{
	return getHip()->getPosition();
}

cocos2d::PhysicsBody *
CompositeLongObject::getBody() const
{
	return getHip()->getBody();
}

ThirdParty::Audio *
CompositeLongObject::getAudio() const
{
	return getHip()->getAudio();
}

bool
CompositeLongObject::isComposed() const
{
	return true;
}

void
CompositeLongObject::setPosition( cocos2d::Vec2 position )
{
	cocos2d::Vec2 curPos = getPosition();
	float deltaX = position.x - curPos.x;
	float deltaY = position.y - curPos.y;
	for( auto obj : _objects )
	{
		cocos2d::Vec2 objsCurPos = obj->getPosition();
		objsCurPos.x += deltaX;
		objsCurPos.y += deltaY;
		obj->setPosition( objsCurPos );
	}
}

void
CompositeLongObject::setSize( cocos2d::Size size )
{
	cocos2d::Size curSize  = getSize();
	cocos2d::Size spriteSize = getContentSize();
	float xScale = size.width / spriteSize.width;
	float yScale = size.height / spriteSize.height;
	float initXScale = curSize.width / spriteSize.width;
	float initYScale = curSize.height / spriteSize.height;
	for( auto obj : _objects )
	{
		cocos2d::Size objCurSize = obj->getSize();
		objCurSize.width /= initXScale;
		objCurSize.height /= initYScale;
		objCurSize.width *= xScale;
		objCurSize.height *= yScale;
		obj->setSize( objCurSize );
	}
}

void
CompositeLongObject::setAdditionalParam( std::string additionalParam )
{
	for( auto obj : _objects )
		obj->setAdditionalParam( additionalParam );
}

void
CompositeLongObject::setRotation( float angle )
{
	for( auto obj : _objects )
		obj->setRotation( angle );
}

void
CompositeLongObject::setScale( cocos2d::Vec2 scale )
{
	for( auto obj : _objects )
		obj->setScale( scale );
}

void
CompositeLongObject::setMask( int mask )
{
	for( auto obj : _objects )
		obj->setMask( mask );
}

void
CompositeLongObject::setColideMask( int colideMask )
{
	for( auto obj : _objects )
		obj->setColideMask( colideMask );
}

void
CompositeLongObject::setContactMask( int contactMask )
{
	for( auto obj : _objects )
		obj->setContactMask( contactMask );
}

void
CompositeLongObject::hide()
{
	for( auto obj : _objects )
		obj->hide();
}

void
CompositeLongObject::show()
{
	for( auto obj : _objects )
		obj->show();
}

LongObject *
CompositeLongObject::getHip() const
{
	for( auto obj : _objects )
		if( obj->getResourcesName() == "Hip" )
			return obj;

	return nullptr;
}

std::vector< LongObject * >
CompositeLongObject::getObjects()
{
	return _objects;
}

void
CompositeLongObject::attachToLevel( Level & level, int zIndex )
{
	for( auto obj : _objects )
		obj->attachToLevel( level, zIndex );
}

}