#include "Spikes.hpp"
#include "Resources/Constants.hpp"

namespace GameAct
{

namespace Objects
{

namespace Requires
{

Interfaces::IObject::Type
Spikes::getType() const
{
	return Interfaces::IObject::Type::Spikes;
}

bool
Spikes::contact(IObject * object)
{
	return object->interact(this);
}

bool
Spikes::interact(GameAct::Objects::Character * character)
{
	return true;
}

cocos2d::Rect
Spikes::getBoundingBox() const
{
	return _node->getBoundingBox();
}
	
cocos2d::PhysicsBody *
Spikes::getPhysicsBody() const
{
	return _node->getPhysicsBody();
}

Spikes::Spikes(cocos2d::Layer * layer)
	: _node(cocos2d::DrawNode::create()), _particle(cocos2d::ParticleSystemQuad::create())
{
	layer->addChild(_node);

	cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();

	/*			ParticlesSetup			*/
	_particle->setEmitterMode(cocos2d::ParticleSystem::Mode::GRAVITY);

	_particle->setTotalParticles(Resources::Constants::DEFAULT_PARTICLE_MAX_COUNT);

	cocos2d::Texture2D * texture = cocos2d::Director::getInstance()->getTextureCache()->addImage("particle.png");
	_particle->setTexture(texture);
	
	_particle->setPosVar(cocos2d::Vec2(size.width, size.height * Resources::Constants::SPIKES_MAX_HEIGT_SCALE / 3.0f));

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

	_particle->setGravity(cocos2d::Vec2(0.0f, size.height * Resources::Constants::DEFAULT_PARTICLE_GRAVITY_SCALE));

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

	//_node->addChild(_particle);
	//_node->runAction(cocos2d::RepeatForever::create(cocos2d::Ripple3D::create(1.0, _node->getBoundingBox().size, _node->getBoundingBox().origin, 50, 20, 1.0f)));
				/**/

	/*			PhysicsSetup			*/
	_node->setPhysicsBody(
		cocos2d::PhysicsBody::createBox(
			cocos2d::Size(size.width, size.height * Resources::Constants::SPIKES_MAX_HEIGT_SCALE),
			cocos2d::PHYSICSBODY_MATERIAL_DEFAULT,
			cocos2d::Vec2(size.width / 2.0f, size.height * Resources::Constants::SPIKES_MAX_HEIGT_SCALE / 2.0f))
	);
	_node->getPhysicsBody()->setDynamic(false);
	_node->getPhysicsBody()->setCategoryBitmask(Resources::Constants::SPIKES_MASK);
	_node->getPhysicsBody()->setCollisionBitmask(Resources::Constants::CHARACTER_MASK);
	_node->getPhysicsBody()->setContactTestBitmask(Resources::Constants::CHARACTER_MASK);
				/**/

	/*			UpdateAction			*/
	auto updateDelta = [this]()
	{
		cocos2d::Vec2 delta(-Resources::Constants::SCENE_SPEED, 0.0f);
		for(Triangle & triangle : _triangles)
		{
			triangle.p1 += delta;
			triangle.p2 += delta;
			triangle.p3 += delta;
		}
	};
	cocos2d::Action * updateAction = cocos2d::RepeatForever::create(
		cocos2d::Sequence::create(
			cocos2d::DelayTime::create(Resources::Constants::FRAME_RATE),
			cocos2d::CallFunc::create(updateDelta),
			cocos2d::CallFunc::create(std::bind(&Spikes::update, this)),
			nullptr
		)
	);
	_node->runAction(updateAction);
					/**/

	fillUp();
}

Spikes::~Spikes()
{
	_node->getPhysicsBody()->removeFromWorld();
	_node->removeComponent(_node->getPhysicsBody());

	_node->removeFromParentAndCleanup(true);
}

void
Spikes::update()
{
	/*			Clearin			*/
	for(auto it = _triangles.begin(); it != _triangles.end();)
	{
		if(it->p1.x < 0.0f && it->p2.x < 0.0f && it->p3.x < 0.0f)
			it = _triangles.erase(it);
		else
			++it;
	}
	_node->clear();
				/**/

	fillUp();

	/*			Rednering			*/
	for(const Triangle & triangle : _triangles)
	{
		cocos2d::Vec2 poly[3] = {triangle.p1, triangle.p2, triangle.p3};
		_node->drawSolidPoly(poly, 3, cocos2d::Color4F::BLACK);
	}
				/**/
}

void
Spikes::fillUp()
{
	/*			Callback			*/
	auto createTriangle = [](cocos2d::Vec2 posit)->Triangle
	{
		cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();
		float koef = 1.1f;
		float maxHeight = size.height * Resources::Constants::SPIKES_MAX_HEIGT_SCALE * koef;
		float minHeight = size.height * Resources::Constants::SPIKES_MIN_HEIGT_SCALE * koef;
		float maxWidth = size.width * Resources::Constants::SPIKES_MAX_WIDTH_SCALE;
		float minWidth = size.width * Resources::Constants::SPIKES_MIN_WIDTH_SCALE;

		float height = cocos2d::RandomHelper::random_real(minHeight, maxHeight);
		float width = cocos2d::RandomHelper::random_real(minWidth, maxWidth);

		Triangle trianle;
		trianle.p1 = posit;
		trianle.p2 = cocos2d::Vec2(posit.x + width / 2.0f, height);
		trianle.p3 = cocos2d::Vec2(posit.x + width, 0.0f);
		return trianle;
	};
				/**/

	cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();

	if(_triangles.size() < 1)
		_triangles.push_back(
			createTriangle(
				cocos2d::Vec2()
			)
		);
	if(_triangles.back().p3.x < size.width * 1.1f)
		while(_triangles.back().p3.x < size.width * 3.0f)
			_triangles.push_back(
				createTriangle(
					_triangles.back().p3 - cocos2d::Vec2(cocos2d::RandomHelper::random_real(0.0f, _triangles.back().p3.x - _triangles.back().p1.x), 0.0f)
				)
			);
}

}

}

}