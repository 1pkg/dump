#include "SpikedBall.hpp"

namespace GameAct
{

namespace Physical
{

void
SpikedBall::initialize()
{
	Object::initialize();

	auto body =  cocos2d::PhysicsBody::createBox( getContentSize() );
	_representation->setPhysicsBody( body );
	getBody()->setDynamic( true );
}

std::string
SpikedBall::getResourcesName() const
{
	return "SpikedBall";
}

}

}