#include "Director.hpp"
#include "GameAct/Act.hpp"
#include "GameAct/Levels/Level.hpp"
#include "GameAct/Objects/Factories/ObjectsFactory.hpp"
#include "Character.hpp"
#include "Resources/Cache/Cache.hpp"

namespace GameAct
{

void
Character::initialize()
{
	CompositeLongObject::initialize();

	auto physicWorld = Director::getInstance().getGameAct()->getLevel()->getPhysicWorld();
	auto size = Director::getInstance().getGameAct()->getLevel()->getLevelSize();

	auto hip = dynamic_cast< LongObject * >( Director::getInstance().getGameAct()->getObjectsFactory()->create( "Hip" ) );

	auto head = dynamic_cast< LongObject * >( Director::getInstance().getGameAct()->getObjectsFactory()->create( "Head" ) );

	auto rightArm = dynamic_cast< LongObject * >( Director::getInstance().getGameAct()->getObjectsFactory()->create( "Arm" ) );
	auto rightHand = dynamic_cast< LongObject * >( Director::getInstance().getGameAct()->getObjectsFactory()->create( "Hand" ) );

	auto leftArm = dynamic_cast< LongObject * >( Director::getInstance().getGameAct()->getObjectsFactory()->create( "Arm" ) );
	auto leftHand = dynamic_cast< LongObject * >( Director::getInstance().getGameAct()->getObjectsFactory()->create( "Hand" ) );

	auto rightLeg = dynamic_cast< LongObject * >( Director::getInstance().getGameAct()->getObjectsFactory()->create( "Leg" ) );
	auto rightFoot = dynamic_cast< LongObject * >( Director::getInstance().getGameAct()->getObjectsFactory()->create( "Foot" ) );

	auto leftLeg = dynamic_cast< LongObject * >( Director::getInstance().getGameAct()->getObjectsFactory()->create( "Leg" ) );
	auto leftFoot = dynamic_cast< LongObject * >( Director::getInstance().getGameAct()->getObjectsFactory()->create( "Foot" ) );

	func = [hip, head, rightArm, rightHand, leftArm, leftHand, rightLeg, leftLeg, rightFoot, leftFoot]()
	{
		cocos2d::Vec2 posit = hip->getPosition();
		cocos2d::Size hipSize = hip->getSize();

		head->setPosition( cocos2d::Vec2( posit.x, posit.y + hipSize.height / 2.0f + head->getSize().height * 0.50f ) );

		rightArm->setPosition( cocos2d::Vec2( posit.x  + hipSize.width / 2.0f, posit.y + hipSize.height / 2.0f - rightArm->getSize().height * 0.65f ) );
		rightHand->setPosition( cocos2d::Vec2( posit.x  + hipSize.width / 2.0f, posit.y + hipSize.height / 2.0f - rightArm->getSize().height * 0.65f - rightHand->getSize().height ) );

		leftArm->setPosition( cocos2d::Vec2( posit.x - hipSize.width / 2.0f, posit.y + hipSize.height / 2.0f - leftArm->getSize().height * 0.65f ) );
		leftHand->setPosition( cocos2d::Vec2( posit.x - hipSize.width / 2.0f, posit.y + hipSize.height / 2.0f - leftArm->getSize().height * 0.65f - leftHand->getSize().height ) );

		rightLeg->setPosition( cocos2d::Vec2( posit.x + hipSize.width * 0.2f, posit.y - hipSize.height / 2.0f - rightLeg->getSize().height * 0.5f ) );
		rightFoot->setPosition( cocos2d::Vec2( posit.x + hipSize.width * 0.2f, posit.y - hipSize.height / 2.0f - rightLeg->getSize().height * 0.5f - rightFoot->getSize().height ) );

		leftLeg->setPosition( cocos2d::Vec2( posit.x - hipSize.width * 0.2f, posit.y - hipSize.height / 2.0f - leftLeg->getSize().height * 0.5f ) );
		leftFoot->setPosition( cocos2d::Vec2( posit.x - hipSize.width * 0.2f, posit.y - hipSize.height / 2.0f - leftLeg->getSize().height * 0.5f - leftFoot->getSize().height ) );

		leftArm->setScale( cocos2d::Vec2( -1.0, 1.0 ) );
		leftHand->setScale( cocos2d::Vec2( -1.0, 1.0 ) );
		leftLeg->setScale( cocos2d::Vec2( -1.0, 1.0 ) );
		leftFoot->setScale( cocos2d::Vec2( -1.0, 1.0 ) );
	};

	_objects.push_back( hip ), _objects.push_back( head ), _objects.push_back( rightArm ), _objects.push_back( rightHand ), _objects.push_back( leftArm ), _objects.push_back( leftHand ), _objects.push_back( rightLeg ), _objects.push_back( rightFoot ), _objects.push_back( leftLeg ), _objects.push_back( leftFoot );
}

std::string
Character::getResourcesName() const
{
	return "Character";
}

void
Character::setSize( cocos2d::Size size )
{
	CompositeLongObject::setSize( size );
	func();
}

void
Character::runAction( const std::string & action )
{
	if( action == "run" )
	{
		for( auto obj : _objects )
			obj->getBody()->setVelocity( cocos2d::Vec2( 0.0f, -150.0f ) );
	}

	if( action == "stop" )
	{
		for( auto obj : _objects )
			obj->getBody()->setVelocity( cocos2d::Vec2( 0.0f, 0.0f ) );
	}

	CompositeLongObject::runAction( action );
}

}