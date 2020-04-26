#include "HelloWorldScene.h"

#include "GameAct\Act.hpp"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(scene->getPhysicsWorld()->DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(cocos2d::Vec2(0.0f, -50.0f));
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
	LayerColor::initWithColor(cocos2d::Color4B::GRAY);

	GameAct::Act::getInstance().restart(this);

	return true;
}

