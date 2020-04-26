#ifndef __ENVIRONMENT_COMMANDS_RICH_CRYPTO_DECRYPTER__
#define __ENVIRONMENT_COMMANDS_RICH_CRYPTO_DECRYPTER__

#include "../../../fwd.hpp"

namespace Environment
{

namespace Commands
{

namespace Rich
{

namespace Crypto
{

class Decrypter : public supps::Command<structs::Buffer, const structs::Buffer &>
{
public:

	Decrypter(std::size_t blockSize, std::array<structs::byte, 32> key, std::array<structs::byte, 32> iv);
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