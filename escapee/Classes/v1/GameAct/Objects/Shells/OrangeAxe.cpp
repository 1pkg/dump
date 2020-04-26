#include "OrangeAxe.hpp"
#include "Resources/Constants.hpp"

namespace GameAct
{

namespace Objects
{

namespace Shells
{

Interfaces::IObject::Type
OrangeAxe::getType() const
{
	return Interfaces::IObject::Type::OrangeAxe;
}

bool
OrangeAxe::contact(IObject * object)
{
	return object->interact(this);
}

cocos2d::Rect
OrangeAxe::getBoundingBox() const
{
	return _sprite->getBoundingBox();
}
	
cocos2d::PhysicsBody *
OrangeAxe::getPhysicsBody() const
{
	return _sprite->getPhysicsBody();
}

OrangeAxe::OrangeAxe(cocos2d::Layer * layer, cocos2d::Vec2 posit)
	: _sprite(cocos2d::Sprite::create("confirmed/orangeaxe.png"))
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

OrangeAxe::~OrangeAxe()
{
	_sprite->getPhysicsBody()->removeFromWorld();
	_sprite->removeComponent(_sprite->getPhysicsBody());

	_sprite->removeFromParentAndCleanup(true);
}

}

}

}