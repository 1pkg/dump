#ifndef __ENVIRONMENT_SUPPORTS_OBJECT__
#define __ENVIRONMENT_SUPPORTS_OBJECT__

#include "Wrapper.hpp"
#include <memory>

namespace Environment
{

namespace Supports
{

class View;
class Object : public Wrapper
{
public:

	virtual View * render() = 0;
};

}

}

#endif