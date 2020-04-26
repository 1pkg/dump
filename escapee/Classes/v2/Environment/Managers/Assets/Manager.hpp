#ifndef __ENVIRONMENT_MANAGERS_ASSETS_MANAGER__
#define __ENVIRONMENT_MANAGERS_ASSETS_MANAGER__

#include  "../../fwd.hpp"
#include "../Commands/Manager.hpp"

namespace Environment
{

namespace Managers
{

namespace Assets
{

class Manager : public supps::Manager<structs::Asset>
{
public:
	
	Manager(Commands::Manager * commander);
	void initialize() override;

private:

	Commands::Manager * _commander;
};

}

}

}

#endif