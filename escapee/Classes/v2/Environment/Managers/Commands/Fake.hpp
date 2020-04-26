#ifndef __ENVIRONMENT_MANAGERS_FAKE__
#define __ENVIRONMENT_MANAGERS_FAKE__

#include "Manager.hpp"

namespace Environment
{

namespace Managers
{

namespace Commands
{

class Fake : public Manager
{
public:

	void initialize() override;
};

}

}

}

#endif