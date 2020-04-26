#ifndef __INTERFACES_IOBJECT_HPP__
#define __INTERFACES_IOBJECT_HPP__

#include "INoncopyable.hpp"

#include <cocos2d.h>

namespace GameAct
{

namespace Contours
{
	class Line;
}

namespace Objects
{
	class Character;

	namespace Requires
	{
		class Spikes;
		class Edge;
	}

	namespace Casters
	{
		class Caster;
	}

	namespace Shells
	{
		class FireBall;
		class FrostBall;
		class FairyBall;
		class DarkBall;
		class Curse;
		class Arrow;
		class Axe;
	}
}

}

namespace Interfaces
{

class IObject : public INoncopyable
{
public:

	enum class Type
	{
		Line,

		Characher,

		Spikes,
		Edge,

		Caster,

		FireBall,
		FrostBall,
		FairyBall,
		DarkBall,
		Curse,
		RedArrow,
		PurpleArrow,
		GreenArrow,
		OrangeAxe,
		BlueAxe,
		YellowSuriken,
		SkyBlueSuriken,

		Non
	};

	virtual ~IObject() =default;

	virtual Type getType() const;

	virtual void runAction(const std::string & action);

	virtual bool contact(IObject * object) =0;

	/*			INTERACTION			*/
	virtual bool interact(GameAct::Contours::Line * line);
	
	virtual bool interact(GameAct::Objects::Character * character);

	virtual bool interact(GameAct::Objects::Requires::Spikes * spikes);
	virtual bool interact(GameAct::Objects::Requires::Edge * edge);

	virtual bool interact(GameAct::Objects::Casters::Caster * caster);

	virtual bool interact(GameAct::Objects::Shells::FireBall * shell);
	virtual bool interact(GameAct::Objects::Shells::FrostBall * shell);
	virtual bool interact(GameAct::Objects::Shells::FairyBall * shell);
	virtual bool interact(GameAct::Objects::Shells::DarkBall * shell);
	virtual bool interact(GameAct::Objects::Shells::Curse * shell);
	virtual bool interact(GameAct::Objects::Shells::Arrow * shell);
	virtual bool interact(GameAct::Objects::Shells::Axe * shell);
				/**/
};

}

#endif