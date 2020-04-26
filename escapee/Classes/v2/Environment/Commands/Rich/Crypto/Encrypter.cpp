#include "Encrypter.hpp"
#include <crypto/aes.h>

namespace Environment
{

namespace Commands
{

namespace Rich
{

namespace Crypto
{

Encrypter::Encrypter(std::size_t blockSize, std::array<structs::byte, 32> key, std::array<structs::byte, 32> iv)
	: _blockSize(blockSize), _key(key), _iv(iv)
{
}

structs::Buffer
Encrypter::execute(const structs::Buffer & buffer)
{
	aes_encrypt_ctx cx[1];
	aes_encrypt_key256(_key.data(), cx);
	structs::Buffer result(buffer.size());
	std::size_t position = 0;
	do
	{
		structs::Buffer block(buffer.block(position, 256));
		position += block.size();
		structs::byte * data = new structs::byte[block.size()];
		aes_cbc_encrypt(block.data(), data, block.size(), _iv.data(), cx);
		result.append(structs::Buffer(data, block.size()));
	}
	while (position != buffer.size());
	return result;
}

}

}

}

}