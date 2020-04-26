#ifndef __ENVIRONMENT_COMMANDS_FAKE_ASSETS_RELATER__
#define __ENVIRONMENT_COMMANDS_FAKE_ASSETS_RELATER__

#include "../../../fwd.hpp"

namespace Environment
{

namespace Commands
{

namespace Rich
{

namespace Assets
{

class Relater : public supps::Command<structs::Buffer, const std::string &, const std::string &>
{
public:

	Relater(supps::Command<structs::Buffer, const std::string &> * fetcher);
	structs::Buffer execute(const std::string & object, const std::string & type) override;

private:

	supps::Command<structs::Buffer, const std::string &> * _featcher;
	supps::Command<structs::Buffer, const std::string &> * _assetsFeatcher;
};

}

}

}

}

#endif