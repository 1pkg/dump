#ifndef __ENVIRONMENT_STRUCTURES_BUFFER__
#define __ENVIRONMENT_STRUCTURES_BUFFER__

#include <memory>

namespace Environment
{

namespace Structures
{

typedef unsigned char byte;

class Buffer
{
public:

	Buffer(std::size_t capacity);
	Buffer(byte * data, std::size_t size);
	Buffer(const Buffer & buffer);
	Buffer & operator=(const Buffer & buffer);
	Buffer(Buffer && buffer);
	Buffer & operator=(Buffer && buffer);
	~Buffer();

	Buffer & append(const Buffer & buffer);
	Buffer & fit(std::size_t size);
	Buffer & expand(std::size_t capacity);
	Buffer block(std::size_t position, std::size_t size) const;
	void clear();
	byte * release();
	byte * data() const;
	std::size_t size() const;
	bool empty() const;

private:

	std::size_t _size;
	std::size_t _capacity;
	byte * _data;
};

}

}

#endif