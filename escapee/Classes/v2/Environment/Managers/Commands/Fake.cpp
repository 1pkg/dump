#include "Fake.hpp"
#include "../../Commands/Fake/Crypto/Encrypter.hpp"
#include "../../Commands/Fake/Crypto/Decrypter.hpp"

namespace Environment
{

namespace Managers
{

namespace Commands
{

void
Fake::initialize()
{
	using namespace Environment::Commands::Fake;
	add("enctypter", std::move(std::unique_ptr<Wrapper>(new Crypto::Encrypter())));
	add("decrypter", std::move(std::unique_ptr<Wrapper>(new Crypto::Decrypter())));
	Manager::initialize();
}

}

}

}