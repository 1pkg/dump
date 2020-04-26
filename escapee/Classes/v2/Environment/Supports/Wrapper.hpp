#ifndef __ENVIRONMENT_SUPPORTS_WRAPPER__
#define __ENVIRONMENT_SUPPORTS_WRAPPER__

namespace Environment
{

namespace Supports
{

class Wrapper
{
public:

	virtual ~Wrapper() = default;
	Wrapper() = default;
	Wrapper(const Wrapper &) = delete;
    Wrapper& operator=(const Wrapper &) = delete;
};

}

}

#endif