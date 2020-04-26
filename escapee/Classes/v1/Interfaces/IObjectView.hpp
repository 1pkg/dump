#ifndef __INTERFACES_IOBJECT_VIEW_HPP__
#define __INTERFACES_IOBJECT_VIEW_HPP__

#include "IObject.hpp"

#include <cocos2d.h>

namespace Interfaces
{

class IObjectView : public IObject
{
public:

	virtual cocos2d::Rect getBoundingBox() const =0;

	virtual cocos2d::PhysicsBody * getPhysicsBody() const =0;
};

}

#endif