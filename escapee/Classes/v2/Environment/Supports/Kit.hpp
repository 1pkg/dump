#ifndef __ENVIRONMENT_SUPPORTS_KIT__
#define __ENVIRONMENT_SUPPORTS_KIT__

#include "Wrapper.hpp"

namespace Environment
{

namespace Supports
{

class Kit : public Wrapper
{
public:

	virtual void update(float dt) = 0;
};

}

}

#endif