#include "Shell.hpp"

namespace GameAct
{

void
Shell::initialize()
{
	Object::initialize();

	cocos2d::PhysicsBody * body = _sprite->getPhysicsBody();
	body->setDynamic( true );
	body->setCategoryBitmask( 0x1 << 2 ); // who ?
	body->setCollisionBitmask( 0x1 << 3 ); // with who ?
	body->setContactTestBitmask( 0x1 << 3 );
}

std::string
Shell::getName() const
{
	return "Shell";
}

}