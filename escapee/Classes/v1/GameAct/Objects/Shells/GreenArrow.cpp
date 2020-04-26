#include "GreenArrow.hpp"
#include "Resources/Constants.hpp"

namespace GameAct
{

namespace Objects
{

namespace Shells
{

Interfaces::IObject::Type
GreenArrow::getType() const
{
	return Interfaces::IObject::Type::GreenArrow;
}

bool
GreenArrow::contact(IObject * object)
{
	return object->interact(this);
}

cocos2d::Rect
GreenArrow::getBoundingBox() const
{
	return _sprite->getBoundingBox();
}
	
cocos2d::PhysicsBody *
GreenArrow::getPhysicsBody() const
{
	return _sprite->getPhysicsBody();
}

GreenArrow::GreenArrow(cocos2d::Layer * layer, cocos2d::Vec2 posit)
	: _sprite(cocos2d::Sprite::create("confirmed/greenarrow.png"))
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

GreenArrow::~RedArrow()
{
	_sprite->getPhysicsBody()->removeFromWorld();
	_sprite->removeComponent(_sprite->getPhysicsBody());

	_sprite->removeFromParentAndCleanup(true);
}

}

}

}