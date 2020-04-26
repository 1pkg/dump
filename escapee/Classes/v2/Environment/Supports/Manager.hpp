#ifndef __ENVIRONMENT_SUPPORTS_MANAGER__
#define __ENVIRONMENT_SUPPORTS_MANAGER__

#include "Wrapper.hpp"
#include "../Structures/Cache.hpp"

namespace Environment
{

namespace Supports
{

template <typename T>
class Manager : public Wrapper, protected Structures::Cache<T>
{
public:
	
	virtual T & create(const std::string & key);
	virtual void initialize() = 0;
};

template <typename T>
T &
Manager<T>::create(const std::string & key)
{
	return get(key);
}

}

}

#endif