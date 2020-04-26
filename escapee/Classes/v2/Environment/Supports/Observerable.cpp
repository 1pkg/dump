#include "Observerable.hpp"

namespace Environment
{

namespace Supports
{

void
Observerable::subscribe(Observer * obs)
{
	_observers.insert(obs);
}

void
Observerable::unsubscribe(Observer * obs)
{
	_observers.erase(obs);
}

}

}