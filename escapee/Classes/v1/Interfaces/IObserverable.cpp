#include "IObserverable.hpp"

namespace Interfaces
{

void
IObserverable::addObserver(Interfaces::IObserver * obs)
{
	_observers.insert(obs);
}

void
IObserverable::removeObserver(Interfaces::IObserver * obs)
{
	_observers.erase(obs);
}

}