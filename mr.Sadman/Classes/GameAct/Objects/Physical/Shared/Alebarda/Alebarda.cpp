#include "Alebarda.hpp"

namespace GameAct
{

namespace Physical
{

void
Alebarda::initialize()
{
	Object::initialize();

	getBody()->setDynamic( false );
}

std::string
Alebarda::getResourcesName() const
{
	return "Alebarda";
}

}

}