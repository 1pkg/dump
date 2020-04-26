#ifndef __ENVIRONMENT_COMMANDS_FAKE_CRYPTO_DECRYPTER__
#define __ENVIRONMENT_COMMANDS_FAKE_CRYPTO_DECRYPTER__

#include "../../../fwd.hpp"

namespace Environment
{

namespace Commands
{

namespace Fake
{

namespace Crypto
{

class Decrypter : public supps::Command<structs::Buffer, const structs::Buffer &>
{
public:

	structs::Buffer execute(const structs::Buffer & buffer) override;
};

}

}

}

}

#endif