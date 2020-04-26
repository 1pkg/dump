#ifndef __ENVIRONMENT_COMMANDS_MIXED_FEATCHERS_FILE__
#define __ENVIRONMENT_COMMANDS_MIXED_FEATCHERS_FILE__

#include "../../fwd.hpp"

namespace Environment
{

namespace Commands
{

namespace Mixed
{

template <typename ... Arguments>
class Formater : public supps::Command<std::string, const std::string &, Arguments ...>
{
public:

	std::string execute(const std::string & pattern, Arguments ... args) override;
};

template <typename ... Arguments>
std::string
Formater<Arguments ... >::execute(const std::string & pattern, Arguments ... args)
{
	char buffer[255] = {0};
	std::sprintf(buffer, pattern, ... args);
	return buffer;
}

}

}

}

#endif