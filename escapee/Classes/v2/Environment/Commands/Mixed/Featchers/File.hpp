#ifndef __ENVIRONMENT_COMMANDS_MIXED_FEATCHERS_FILE__
#define __ENVIRONMENT_COMMANDS_MIXED_FEATCHERS_FILE__

#include "../../../fwd.hpp"

namespace Environment
{

namespace Commands
{

namespace Mixed
{

namespace Featchers
{

class File : public supps::Command<structs::Buffer, const std::string &>
{
public:

	File(supps::Command<structs::Buffer, const structs::Buffer &> * decrypter);
	structs::Buffer execute(const std::string & file) override;

private:

	supps::Command<structs::Buffer, const structs::Buffer &> * _decrypter;
};

}

}

}

}

#endif