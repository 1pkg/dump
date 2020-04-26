#ifndef __ENVIRONMENT_SUPPORTS_VIEW__
#define __ENVIRONMENT_SUPPORTS_VIEW__

#include "Wrapper.hpp"
#include <cocos2d.h>

namespace Environment
{

namespace Supports
{

class View : public Wrapper
{
public:

	virtual void attach(cocos2d::Layer *) = 0;
};

}

}

#endif