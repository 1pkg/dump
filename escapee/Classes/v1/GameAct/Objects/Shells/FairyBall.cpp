#include "FireBall.hpp"
#include "Resources/Constants.hpp"

namespace GameAct
{

namespace Objects
{

namespace Shells
{

Interfaces::IObject::Type
FireBall::getType() const
{
	return Interfaces::IObject::Type::FireBall;
}

bool
FireBall::contact(IObject * object)
{
	return object->interact(this);
}

cocos2d::Rect
FireBall::getBoundingBox() const
{
	return cocos2d::Rect();
}
	
cocos2d::PhysicsBody *
FireBall::getPhysicsBody() const
{
	return _particle->getPhysicsBody();
}

FireBall::FireBall(cocos2d::Layer * layer, cocos2d::Vec2 posit)
	: _particle(cocos2d::ParticleSystemQuad::create())
{
	cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();

	_particle->setPosition(posit);

	/*			ParticlesSetup			*/
	_particle->setEmitterMode(cocos2d::ParticleSystem::Mode::GRAVITY);

	_particle->setTotalParticles(Resources::Constants::DEFAULT_PARTICLE_MAX_COUNT/20.0f);

	cocos2d::Texture2D * texture = cocos2d::Director::getInstance()->getTextureCache()->addImage("particle.png");
	_particle->setTexture(texture);
	
	_particle->setPosVar(cocos2d::Vec2(5.0f, 5.0f));

	_particle->setDuration(-1);

	_particle->setEmissionRate(Resources::Constants::DEFAULT_PARTICLE_EMISSION_RATE);

	_particle->setLife(Resources::Constants::DEFAULT_PARTICLE_LIFE_TIME);
	_particle->setLifeVar(Resources::Constants::DEFAULT_PARTICLE_LIFE_TIME * 0.5f);

	_particle->setStartColor(cocos2d::Color4F::RED);
	_particle->setStartColorVar(cocos2d::Color4F::BLACK);
	_particle->setEndColor(cocos2d::Color4F::ORANGE);
	_particle->setEndColorVar(cocos2d::Color4F::BLACK);

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
	_particle->setPhysicsBody(cocos2d::PhysicsBody::createCircle(10.0f));
	_particle->getPhysicsBody()->setCategoryBitmask(Resources::Constants::SHELL_MASK);
	_particle->getPhysicsBody()->setCollisionBitmask(Resources::Constants::CHARACTER_MASK);
	_particle->getPhysicsBody()->setContactTestBitmask(Resources::Constants::CHARACTER_MASK);
	_particle->getPhysicsBody()->applyImpulse(cocos2d::Vec2(-30000.0f, 0.0f));
				/**/
}

FireBall::~FireBall()
{
	_particle->getPhysicsBody()->removeFromWorld();
	_particle->removeComponent(_particle->getPhysicsBody());

	_particle->removeFromParentAndCleanup(true);
}

}

}

}