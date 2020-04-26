#include "IObject.hpp"

namespace Interfaces
{

IObject::Type
IObject::getType() const
{
	return Type::Non;
}

void
IObject::runAction(const std::string & action)
{
	return;
}

bool
IObject::interact(GameAct::Contours::Line * line)
{
	return false;
}
	
bool
IObject::interact(GameAct::Objects::Character * character)
{
	return false;
}

bool
IObject::interact(GameAct::Objects::Requires::Spikes * spikes)
{
	return false;
}

bool
IObject::interact(GameAct::Objects::Requires::Edge * edge)
{
	return false;
}

bool
IObject::interact(GameAct::Objects::Casters::Caster * caster)
{
	return false;
}

bool
IObject::interact(GameAct::Objects::Shells::FireBall * caster)
{
	return false;
}

bool
IObject::interact(GameAct::Objects::Shells::FrostBall * caster)
{
	return false;
}

bool
IObject::interact(GameAct::Objects::Shells::FairyBall * caster)
{
	return false;
}

bool
IObject::interact(GameAct::Objects::Shells::DarkBall * caster)
{
	return false;
}

bool
IObject::interact(GameAct::Objects::Shells::Curse * caster)
{
	return false;
}

bool
IObject::interact(GameAct::Objects::Shells::Arrow * caster)
{
	return false;
}

bool
IObject::interact(GameAct::Objects::Shells::Axe * caster)
{
	return false;
}

}