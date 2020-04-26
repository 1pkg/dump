#include "Interactor.hpp"

namespace GameAct
{

namespace Objects
{

bool
Interactor::interact(Interfaces::IObject * lobject, Interfaces::IObject * robject)
{
	return lobject->contact(robject);
}

}

}