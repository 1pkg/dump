#include "Rich.hpp"
#include "../../Commands/Rich/Crypto/Encrypter.hpp"
#include "../../Commands/Rich/Crypto/Decrypter.hpp"

namespace Environment
{

namespace Managers
{

namespace Commands
{

void
Rich::initialize()
{
	using namespace Environment::Commands::Rich;
	std::size_t size = 256;
	std::array<structs::byte, 32> key =	{'7','1','8','5','8','0','4','5','1','1','1','4','9','9','7','2','2','0','5','7','1','7','2','5','2','2','2','5','7','0','7','4'};
	std::array<structs::byte, 32> iv = {'8','5','3','0','4','8','6','6','5','0','6','9','1','6','2','3','3','4','3','9','4','9','8','2','9','3','0','9','8','1','8','6'};
	add("encrypter", std::move(std::unique_ptr<Wrapper>(new Crypto::Encrypter(size, key, iv))));
	add("decrypter", std::move(std::unique_ptr<Wrapper>(new Crypto::Decrypter(size, key, iv))));
	Manager::initialize();
}

}

}

}