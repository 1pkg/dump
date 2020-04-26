#include "Character.hpp"
#include "../Contours/Kit.hpp"
#include "../Contours/KitExpert.hpp"
#include "Resources/Constants.hpp"

#include "ThirdParty/Extensions/VerticalFollow.hpp"

#include <spine/SkeletonAnimation.h>

namespace GameAct
{

namespace Objects
{

Interfaces::IObject::Type
Character::getType() const
{
	return Interfaces::IObject::Type::Characher;
}

bool
Character::contact(IObject * object)
{
	return object->interact(this);
}

bool
Character::interact(GameAct::Contours::Line * line)
{
	return true;
}

bool
Character::interact(GameAct::Objects::Requires::Spikes * spikes)
{
	return true;
}

bool
Character::interact(GameAct::Objects::Requires::Edge * edge)
{
	return true;
}

cocos2d::Rect
Character::getBoundingBox() const
{
	cocos2d::Rect rect = _node->getBoundingBox();
	return _node->getBoundingBox();
}
	
cocos2d::PhysicsBody *
Character::getPhysicsBody() const
{
	return _node->getPhysicsBody();
}

void
Character::nortify() const
{
	for(Interfaces::IObserver * obs : _observers)
		obs->handle(this);
}

Character::Character(const Contours::KitExpert & kitExpert, cocos2d::Layer * layer)
	: _layer(layer), _node(spine::SkeletonAnimation::createWithFile("spineboy.json", "spineboy.atlas", 0.1f))
{
	_layer->addChild(_node, 6);
	_node->setPosition(cocos2d::Vec2(300.0f, 200.0f));
	_node->addAnimation(0, "run", true);
	_node->updateWorldTransform();

	cocos2d::Rect rect = _node->getBoundingBox();
	auto body = cocos2d::PhysicsBody::createBox(rect.size, cocos2d::PHYSICSBODY_MATERIAL_DEFAULT, cocos2d::Vec2(0.0f, rect.size.height / 2));
	body->setRotationEnable(false);
	_node->setPhysicsBody(body);

	_node->getPhysicsBody()->applyForce(cocos2d::Vec2(10000.0f, 0.0f));
	_node->getPhysicsBody()->setVelocityLimit(50.0f);
	_node->getPhysicsBody()->setCategoryBitmask(Resources::Constants::CHARACTER_MASK);
	_node->getPhysicsBody()->setCollisionBitmask(Resources::Constants::LINE_MASK | Resources::Constants::SPIKES_MASK);
	_node->getPhysicsBody()->setContactTestBitmask(Resources::Constants::LINE_MASK | Resources::Constants::SPIKES_MASK);

	auto checker = cocos2d::CallFunc::create([&kitExpert, this]()
	{
		if(kitExpert.isEndOfSegment(cocos2d::Vec2(_node->getPosition().x, _node->getPosition().y + 30.0f - 45.0f/2), 50.0f))
		{
			_node->getPhysicsBody()->applyImpulse(cocos2d::Vec2(0.0f, 3000.0f));
			_node->addAnimation(1, "jump", false);
		}
	});
	_updateAction =
		cocos2d::RepeatForever::create(
			cocos2d::Sequence::create(
				cocos2d::DelayTime::create(1.0f),
				checker,
				cocos2d::CallFunc::create(std::bind(&Character::nortify, this)),
				nullptr
			)
		);
	_node->runAction(_updateAction);

	cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();
	_followAction =
		ThirdParty::Extensions::VerticalFollow::create(
			_node,
			std::pair<float, float>{
				size.height / 2.0f,
				size.height * (Resources::Constants::SCENE_HEIGHT_SCALE - 0.5f)
			}
		);
	_layer->runAction(_followAction);
}

Character::~Character()
{
	_layer->stopAction(_followAction);

	_node->stopAction(_updateAction);
	_node->removeFromParentAndCleanup(true);
}

void
Character::assignView(Interfaces::IViewPort * view)
{
	ThirdParty::Extensions::VerticalFollow * follow = (ThirdParty::Extensions::VerticalFollow *)_followAction;
	follow->_fixedViews.insert(view);

	_view.insert(view);
}

}

}