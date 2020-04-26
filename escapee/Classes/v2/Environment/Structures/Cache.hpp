#ifndef __ENVIRONMENT_STRUCTURES_CACHE__
#define __ENVIRONMENT_STRUCTURES_CACHE__

#include <string>
#include <unordered_map>

namespace Environment
{

namespace Structures
{

template<typename T>
class Cache
{
protected:

	void add(const std::string & key, T & value);
	void remove(const std::string & key);
	T & get(const std::string & key);
	bool has(const std::string & key) const;

	std::unordered_map<std::string, T> _map;
};

template<typename T>
void
Cache<T>::add(const std::string & key, T & value)
{
	_map.insert({key, std::move(value)});
}

template<typename T>
void
Cache<T>::remove(const std::string & key)
{
	_map.erase(key);
}

template<typename T>
T &
Cache<T>::get(const std::string & key)
{
	return _map.at(key);
}

template<typename T>
bool
Cache<T>::has(const std::string & key) const
{
	return _map.find(key) != _map.end();
}

}

}

#endif