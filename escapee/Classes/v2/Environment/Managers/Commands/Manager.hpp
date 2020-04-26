#ifndef __ENVIRONMENT_MANAGERS_COMMANDS_MANAGER__
#define __ENVIRONMENT_MANAGERS_COMMANDS_MANAGER__

#include  "../../fwd.hpp"

namespace Environment
{

namespace Managers
{

namespace Commands
{

class Manager : public supps::Manager<std::unique_ptr<supps::Wrapper>>
{
public:
	
	template <typename Result, typename ... Arguments>
	supps::Command<Result, Arguments ...> * command(const std::string & command);
	void initialize() override;
};

template <typename Result, typename ... Arguments>
supps::Command<Result, Arguments ...> *
Manager::command(const std::string & command)
{
	return dynamic_cast<supps::Command<Result, Arguments ...> *>(create(command).get());
}

}

}

}

#endif