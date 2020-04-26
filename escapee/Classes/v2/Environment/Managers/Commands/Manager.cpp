#include "Manager.hpp"
#include "../../Commands/Mixed/Featchers/File.hpp"

namespace Environment
{

namespace Managers
{

namespace Commands
{

void
Manager::initialize()
{
	supps::Command<structs::Buffer, const structs::Buffer &> * dectypter = command<structs::Buffer, const structs::Buffer &>("decrypter");
	using namespace Environment::Commands::Mixed;
	add("file_featcher", std::move(std::unique_ptr<Wrapper>(new Featchers::File(dectypter))));
}

}

}

}