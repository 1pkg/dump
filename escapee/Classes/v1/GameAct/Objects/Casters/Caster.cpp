#include "Caster.hpp"
#include "../Shells/FireBall.hpp"
#include "Resources/Constants.hpp"

namespace GameAct
{

namespace Objects
{

namespace Casters
{

Interfaces::IObject::Type
Caster::getType() const
{
	return Interfaces::IObject::Type::Caster;
}

bool
Caster::contact(IObject * object)
{
	return object->interact(this);
}

cocos2d::Rect
Caster::getBoundingBox() const
{
	return cocos2d::Rect();
}
	
cocos2d::PhysicsBody *
Caster::getPhysicsBody() const
{
	return _sprite->getPhysicsBody();
}

Caster::Caster(cocos2d::Layer * layer)
	: _sprite(cocos2d::Sprite::create("caster.jpg")), _layer(layer)
{
	cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();

	_sprite->setPosition(600.0f, 400.0f);
	_layer->addChild(_sprite);

	/*			PhysicsSetup			*/
	_sprite->setPhysicsBody(cocos2d::PhysicsBody::createBox(_sprite->getContentSize()));
	_sprite->getPhysicsBody()->setDynamic(false);
	_sprite->getPhysicsBody()->setCategoryBitmask(Resources::Constants::CASTER_MASK);
	_sprite->getPhysicsBody()->setCollisionBitmask(Resources::Constants::CHARACTER_MASK);
	_sprite->getPhysicsBody()->setContactTestBitmask(Resources::Constants::CHARACTER_MASK);
				/**/

	cast();
	cast();
	cast();
}

Caster::~Caster()
{
	_sprite->getPhysicsBody()->removeFromWorld();
	_sprite->removeComponent(_sprite->getPhysicsBody());

	_sprite->removeFromParentAndCleanup(true);
}

void
Caster::cast()
{
	Shells::FireBall * shell = new Shells::FireBall(_layer, _sprite->getPosition() - _sprite->getContentSize()/2);
}

}

}

}