#ifndef __ENVIRONMENT_SUPPORTS_COMMAND__
#define __ENVIRONMENT_SUPPORTS_COMMAND__

#include "Wrapper.hpp"

namespace Environment
{

namespace Supports
{

template <typename Result, typename ... Arguments>
class Command : public Wrapper
{
public:

	virtual Result execute(Arguments ... args) = 0;
};

}

}

#endif