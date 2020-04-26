#ifndef __GAME_ACT_FORWARD_INTERACTOR_HPP__
#define __GAME_ACT_FORWARD_INTERACTOR_HPP__

namespace GameAct
{

namespace Tech
{

	class Ball;
	class Barell;
	class Block;
	class Bullets;
	class Cannon;
	class CannonOneOff;
	class Dynamite;
	class Electricity;
	class Flame;
	class FlameThrower;
	class Gear;
	class Gum;
	class Impeller;
	class Line;
	class MachineGun;
	class Poision;
	class Radiation;
	class Saw;
	class Spike;
	class Wind;
	class WindDecorate;
	
}

class Edge;
class Character;

class Interactor
{
public:

	virtual void interact( Tech::Ball * obj );
	virtual void interact( Tech::Barell * obj );
	virtual void interact( Tech::Block * obj );
	virtual void interact( Tech::Bullets * obj );
	virtual void interact( Tech::Cannon * obj );
	virtual void interact( Tech::CannonOneOff * obj );
	virtual void interact( Tech::Dynamite * obj );
	virtual void interact( Tech::Electricity * obj );
	virtual void interact( Tech::Flame * obj );
	virtual void interact( Tech::FlameThrower * obj );
	virtual void interact( Tech::Gear * obj );
	virtual void interact( Tech::Gum * obj );
	virtual void interact( Tech::Impeller * obj );
	virtual void interact( Tech::Line * obj );
	virtual void interact( Tech::MachineGun * obj );
	virtual void interact( Tech::Poision * obj );
	virtual void interact( Tech::Radiation * obj );
	virtual void interact( Tech::Saw * obj );
	virtual void interact( Tech::Spike * obj );
	virtual void interact( Tech::Wind * obj );
	virtual void interact( Tech::WindDecorate * obj );

	virtual void interact( Edge * obj );

	virtual void interact( Character * obj );
};

}

#endif