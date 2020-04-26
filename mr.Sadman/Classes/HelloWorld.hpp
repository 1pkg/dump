#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene();
	static HelloWorld * create( cocos2d::PhysicsWorld * world );

    virtual bool init( cocos2d::PhysicsWorld * world );
};

#endif // __HELLOWORLD_SCENE_H__
