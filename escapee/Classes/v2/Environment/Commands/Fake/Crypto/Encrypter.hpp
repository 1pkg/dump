#ifndef __ENVIRONMENT_COMMANDS_FAKE_CRYPTO_ENCRYPTER__
#define __ENVIRONMENT_COMMANDS_FAKE_CRYPTO_ENCRYPTER__

#include "../../../fwd.hpp"

namespace Environment
{

namespace Commands
{

namespace Fake
{

namespace Crypto
{

class Encrypter : public supps::Command<structs::Buffer, const structs::Buffer &>
{
public:

	structs::Buffer execute(const structs::Buffer & buffer) override;
};

}

}

}

}

#endif