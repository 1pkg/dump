#include "BlueAxe.hpp"
#include "Resources/Constants.hpp"

namespace GameAct
{

namespace Objects
{

namespace Shells
{

Interfaces::IObject::Type
BlueAxe::getType() const
{
	return Interfaces::IObject::Type::BlueAxe;
}

bool
BlueAxe::contact(IObject * object)
{
	return object->interact(this);
}

cocos2d::Rect
BlueAxe::getBoundingBox() const
{
	return _sprite->getBoundingBox();
}
	
cocos2d::PhysicsBody *
BlueAxe::getPhysicsBody() const
{
	return _sprite->getPhysicsBody();
}

BlueAxe::BlueAxe(cocos2d::Layer * layer, cocos2d::Vec2 posit)
	: _sprite(cocos2d::Sprite::create("confirmed/blueaxe.png"))
{
	_sprite->setPosition(posit);

	/*			PhysicsSetup			*/
	_sprite->setPhysicsBody(cocos2d::PhysicsBody::createBox(_sprite->getContentSize()));
	_sprite->getPhysicsBody()->setCategoryBitmask(Resources::Constants::SHELL_MASK);
	_sprite->getPhysicsBody()->setCollisionBitmask(Resources::Constants::CHARACTER_MASK);
	_sprite->getPhysicsBody()->setContactTestBitmask(Resources::Constants::CHARACTER_MASK);
	_sprite->getPhysicsBody()->applyImpulse(cocos2d::Vec2(-30000.0f, 0.0f));
				/**/
}

BlueAxe::~BlueAxe()
{
	_sprite->getPhysicsBody()->removeFromWorld();
	_sprite->removeComponent(_sprite->getPhysicsBody());

	_sprite->removeFromParentAndCleanup(true);
}

}

}

}