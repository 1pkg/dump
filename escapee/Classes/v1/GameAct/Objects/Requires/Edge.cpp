#include "Edge.hpp"
#include "Resources/Constants.hpp"

namespace GameAct
{

namespace Objects
{

namespace Requires
{

Interfaces::IObject::Type
Edge::getType() const
{
	return Interfaces::IObject::Type::Edge;
}

bool
Edge::contact(IObject * object)
{
	return object->interact(this);
}

bool
Edge::interact(GameAct::Objects::Character * character)
{
	return true;
}

cocos2d::Rect
Edge::getBoundingBox() const
{
	return cocos2d::Rect();
}
	
cocos2d::PhysicsBody *
Edge::getPhysicsBody() const
{
	return _particle->getPhysicsBody();
}

Edge::Edge(cocos2d::Layer * layer)
	: _particle(cocos2d::ParticleSystemQuad::create())
{
	cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();

	/*			ParticlesSetup			*/
	_particle->setEmitterMode(cocos2d::ParticleSystem::Mode::GRAVITY);

	_particle->setTotalParticles(Resources::Constants::DEFAULT_PARTICLE_MAX_COUNT);

	cocos2d::Texture2D * texture = cocos2d::Director::getInstance()->getTextureCache()->addImage("particle.png");
	_particle->setTexture(texture);
	
	_particle->setPosVar(cocos2d::Vec2(size.width * Resources::Constants::EDGE_WIDTH_SCALE, size.height * Resources::Constants::SCENE_HEIGHT_SCALE));

	_particle->setDuration(-1);

	_particle->setEmissionRate(Resources::Constants::DEFAULT_PARTICLE_EMISSION_RATE);

	_particle->setLife(Resources::Constants::DEFAULT_PARTICLE_LIFE_TIME);
	_particle->setLifeVar(Resources::Constants::DEFAULT_PARTICLE_LIFE_TIME * 0.5f);

	_particle->setStartColor(cocos2d::Color4F::WHITE);
	_particle->setStartColorVar(cocos2d::Color4F::WHITE);
	_particle->setEndColor(cocos2d::Color4F::WHITE);
	_particle->setEndColorVar(cocos2d::Color4F::WHITE);

	_particle->setStartSize((size.width + size.height) / 2.0f * Resources::Constants::DEFAULT_PARTICLE_SIZE_SCALE);
	_particle->setStartSizeVar((size.width + size.height) / 4.0f * Resources::Constants::DEFAULT_PARTICLE_SIZE_SCALE);
	_particle->setEndSize((size.width + size.height) / 2.0f * Resources::Constants::DEFAULT_PARTICLE_SIZE_SCALE);
	_particle->setStartSizeVar((size.width + size.height) / 4.0f * Resources::Constants::DEFAULT_PARTICLE_SIZE_SCALE);

	_particle->setGravity(cocos2d::Vec2(size.width * Resources::Constants::DEFAULT_PARTICLE_GRAVITY_SCALE, 0.0f));

	_particle->setStartSpin(0.0f);
	_particle->setStartSizeVar(0.0f);
	_particle->setEndSpin(0.0f);
	_particle->setEndSpinVar(0.0f);

	_particle->setAngle(90.0f);
	_particle->setAngleVar(0.0f);

	_particle->setSpeed(0.0f);
	_particle->setSpeedVar(0.0f);

	_particle->setTangentialAccel(0.0f);
	_particle->setTangentialAccelVar(0.0f);

	_particle->setRadialAccel(0.0f);
	_particle->setRadialAccelVar(0.0f);

	layer->addChild(_particle);
				/**/

	/*			PhysicsSetup			*/
	_particle->setPhysicsBody(
		cocos2d::PhysicsBody::createBox(
			cocos2d::Size(size.width * Resources::Constants::EDGE_WIDTH_SCALE, size.height * Resources::Constants::SCENE_HEIGHT_SCALE),
			cocos2d::PHYSICSBODY_MATERIAL_DEFAULT,
			cocos2d::Vec2(size.width * Resources::Constants::EDGE_WIDTH_SCALE / 2.0f, size.height * Resources::Constants::SPIKES_MAX_HEIGT_SCALE / 2.0f))
	);
	_particle->getPhysicsBody()->setDynamic(false);
	_particle->getPhysicsBody()->setCategoryBitmask(Resources::Constants::SPIKES_MASK);
	_particle->getPhysicsBody()->setCollisionBitmask(Resources::Constants::CHARACTER_MASK);
	_particle->getPhysicsBody()->setContactTestBitmask(Resources::Constants::CHARACTER_MASK);
				/**/
}

Edge::~Edge()
{
	_particle->getPhysicsBody()->removeFromWorld();
	_particle->removeComponent(_particle->getPhysicsBody());

	_particle->removeFromParentAndCleanup(true);
}

}

}

}