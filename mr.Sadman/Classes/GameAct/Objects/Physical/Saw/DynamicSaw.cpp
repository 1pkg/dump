#include "DynamicSaw.hpp"

namespace GameAct
{

namespace Physical
{

void
DynamicSaw::initialize()
{
	StaticSaw::initialize();

	getBody()->setDynamic( true );
}

}

}