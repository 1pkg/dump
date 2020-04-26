#ifndef __RESOURCES_OBJECT_INFO_HPP__
#define __RESOURCES_OBJECT_INFO_HPP__

#include <cocos2d.h>

namespace Resources
{

class ObjectInfo
{
public:

	ObjectInfo();

	std::string name;

	cocos2d::Vec2 position;
	cocos2d::Size size;

	float angle;
	cocos2d::Vec2 scale;

	int zIndex;

	int mask;
	int collideMask;
	int contactMask;

	std::string additionalParam;

	std::string initAction;

	std::vector< ObjectInfo > slaves;
};

}

#endif