#include "Manager.hpp"

namespace Environment
{

namespace Managers
{

namespace Assets
{

Manager::Manager(Commands::Manager * commander)
	: _commander(commander)
{
}

void
Manager::initialize()
{
	supps::Command<structs::Buffer, const std::string &> * fetcher = _commander->command<structs::Buffer, const std::string &>("file_featcher");
}

}

}

}