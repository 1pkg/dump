#ifndef __ENVIRONMENT_MANAGERS_RICH__
#define __ENVIRONMENT_MANAGERS_RICH__

#include "Manager.hpp"

namespace Environment
{

namespace Managers
{

namespace Commands
{

class Rich : public Manager
{
public:

	void initialize() override;
};

}

}

}

#endif