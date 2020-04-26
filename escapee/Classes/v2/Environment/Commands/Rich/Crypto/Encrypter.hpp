#ifndef __ENVIRONMENT_COMMANDS_RICH_CRYPTO_ENCRYPTER__
#define __ENVIRONMENT_COMMANDS_RICH_CRYPTO_ENCRYPTER__

#include "../../../fwd.hpp"

namespace Environment
{

namespace Commands
{

namespace Rich
{

namespace Crypto
{

class Encrypter : public supps::Command<structs::Buffer, const structs::Buffer &>
{
public:

	Encrypter(std::size_t blockSize, std::array<structs::byte, 32> key, std::array<structs::byte, 32> iv);
	structs::Buffer execute(const structs::Buffer & buffer) override;

private:

	std::size_t _blockSize;
	std::array<structs::byte, 32> _key, _iv;
};

}

}

}

}

#endif