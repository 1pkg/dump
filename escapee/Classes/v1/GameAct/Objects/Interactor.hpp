#ifndef __GAME_ACT_OBECTS_INTERACTOR_HPP__
#define __GAME_ACT_OBECTS_INTERACTOR_HPP__

#include "Interfaces/IObject.hpp"

namespace GameAct
{

namespace Objects
{

class Interactor : public Interfaces::INoncopyable
{
public:

	bool interact(Interfaces::IObject * lobject, Interfaces::IObject * robject);

};

}

}

#endif