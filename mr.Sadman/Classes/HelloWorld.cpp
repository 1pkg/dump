#include "Director.hpp"
#include "Resources/Forward.hpp"
#include "HelloWorld.hpp"
#include "GameAct/Act.hpp"
#include "GameAct/Levels/Level.hpp"

#include <string>
#include <unordered_set>

HelloWorld *
HelloWorld::create( cocos2d::PhysicsWorld * world )
{
    HelloWorld *pRet = new( std::nothrow ) HelloWorld();
    if ( pRet && pRet->init( world ) )
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

cocos2d::Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = cocos2d::Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask( scene->getPhysicsWorld()->DEBUGDRAW_ALL );
	scene->getPhysicsWorld()->setGravity( cocos2d::Vec2( 0.0f, 0.0f ) );
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create( scene->getPhysicsWorld() );

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init( cocos2d::PhysicsWorld * world )
{
   if ( !cocos2d::CCLayer::init() )
    {
        return false;
    }

	Director::getInstance().restartAct( Resources::Lab::Physical, -3, this, world );

	auto res = cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->executeString("var a = 10; cc.log('this is a log');");

	auto listener = cocos2d::EventListenerKeyboard::create(); 
	listener->onKeyPressed = [this]( cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event ){

		if( keyCode == cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE )
		{
			Director::getInstance().finishAct();
			cocos2d::Director::getInstance()->end();
		}

		/*if( keyCode == cocos2d::EventKeyboard::KeyCode::KEY_SPACE )
			Director::getInstance().getGameAct()->getCharacter()->runAction( "stop" );

		if( keyCode == cocos2d::EventKeyboard::KeyCode::KEY_SHIFT )
			Director::getInstance().getGameAct()->getCharacter()->runAction( "run" );*/
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority( listener, this );
	setScale( 0.001f );

    return true;
}