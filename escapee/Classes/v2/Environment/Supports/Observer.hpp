#ifndef __ENVIRONMENT_SUPPORTS_OBSERVER__
#define __ENVIRONMENT_SUPPORTS_OBSERVER__

#include "Wrapper.hpp"

namespace Environment
{

namespace Supports
{

class Observerable;
class Observer : public Wrapper
{
public:

	virtual bool handle(Observerable * observerable) = 0;
};

}

}

#endif