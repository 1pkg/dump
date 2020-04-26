#include "CompositeObject.hpp"

namespace GameAct
{

void
CompositeObject::initialize()
{
	_representation = nullptr;
	_audio = nullptr;
}

cocos2d::Size
CompositeObject::getSize() const
{
	return getHip()->getSize();
}

cocos2d::Size
CompositeObject::getContentSize() const
{
	return getHip()->getContentSize();
}

cocos2d::Vec2
CompositeObject::getPosition() const
{
	return getHip()->getPosition();
}

cocos2d::PhysicsBody *
CompositeObject::getBody() const
{
	return getHip()->getBody();
}

ThirdParty::Audio *
CompositeObject::getAudio() const
{
	return getHip()->getAudio();
}

bool
CompositeObject::isComposed() const
{
	return true;
}

void
CompositeObject::setPosition( cocos2d::Vec2 position )
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
CompositeObject::setSize( cocos2d::Size size )
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
CompositeObject::setAdditionalParam( std::string additionalParam )
{
	for( auto obj : _objects )
		obj->setAdditionalParam( additionalParam );
}

void
CompositeObject::setRotation( float angle )
{
	for( auto obj : _objects )
		obj->setRotation( angle );
}

void
CompositeObject::setScale( cocos2d::Vec2 scale )
{
	for( auto obj : _objects )
		obj->setScale( scale );
}

void
CompositeObject::setMask( int mask )
{
	for( auto obj : _objects )
		obj->setMask( mask );
}

void
CompositeObject::setColideMask( int colideMask )
{
	for( auto obj : _objects )
		obj->setColideMask( colideMask );
}

void
CompositeObject::setContactMask( int contactMask )
{
	for( auto obj : _objects )
		obj->setContactMask( contactMask );
}

void
CompositeObject::hide()
{
	for( auto obj : _objects )
		obj->hide();
}

void
CompositeObject::show()
{
	for( auto obj : _objects )
		obj->show();
}

Object *
CompositeObject::getHip() const
{
	for( auto obj : _objects )
		if( obj->getResourcesName() == "Hip" )
			return obj;

	return nullptr;
}

std::vector< Object * >
CompositeObject::getObjects()
{
	return _objects;
}

void
CompositeObject::attachToChunk( Chunk & chunk, int zIndex )
{
	for( auto obj : _objects )
		obj->attachToChunk( chunk, zIndex );
}

}