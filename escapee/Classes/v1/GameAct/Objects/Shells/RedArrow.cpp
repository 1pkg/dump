#include "RedArrow.hpp"
#include "Resources/Constants.hpp"

namespace GameAct
{

namespace Objects
{

namespace Shells
{

Interfaces::IObject::Type
RedArrow::getType() const
{
	return Interfaces::IObject::Type::RedArrow;
}

bool
RedArrow::contact(IObject * object)
{
	return object->interact(this);
}

cocos2d::Rect
RedArrow::getBoundingBox() const
{
	return _sprite->getBoundingBox();
}
	
cocos2d::PhysicsBody *
RedArrow::getPhysicsBody() const
{
	return _sprite->getPhysicsBody();
}

RedArrow::RedArrow(cocos2d::Layer * layer, cocos2d::Vec2 posit)
	: _sprite(cocos2d::Sprite::create("confirmed/redarrow.png"))
{
	_sprite->setPosition(posit);

	cocos2d::Size size = _sprite->getContentSize();

	/*			PhysicsSetup			*/
	_sprite->setPhysicsBody(cocos2d::PhysicsBody::createBox(cocos2d::Size(size.width, size.height / 4.0f), cocos2d::PHYSICSBODY_MATERIAL_DEFAULT, cocos2d::Vec2(0.0f, size.height / 2)));
	_sprite->getPhysicsBody()->setCategoryBitmask(Resources::Constants::SHELL_MASK);
	_sprite->getPhysicsBody()->setCollisionBitmask(Resources::Constants::CHARACTER_MASK);
	_sprite->getPhysicsBody()->setContactTestBitmask(Resources::Constants::CHARACTER_MASK);
	_sprite->getPhysicsBody()->applyImpulse(cocos2d::Vec2(-30000.0f, 0.0f));
				/**/
}

RedArrow::~RedArrow()
{
	_sprite->getPhysicsBody()->removeFromWorld();
	_sprite->removeComponent(_sprite->getPhysicsBody());

	_sprite->removeFromParentAndCleanup(true);
}

}

}

}