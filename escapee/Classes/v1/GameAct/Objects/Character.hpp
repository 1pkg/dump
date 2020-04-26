#ifndef __GAME_ACT_OBECTS_CHARATER_HPP__
#define __GAME_ACT_OBECTS_CHARATER_HPP__

#include "Interfaces/IObjectView.hpp"
#include "Interfaces/IViewPort.hpp"
#include "Interfaces/IObserverable.hpp"
#include "Interfaces/IObserver.hpp"

#include <cocos2d.h>

#include <unordered_set>

namespace spine
{
	class SkeletonAnimation;
}

namespace GameAct
{

namespace Contours
{
	class KitExpert;
}

namespace Objects
{

class Character : public Interfaces::IObjectView, public Interfaces::IObserverable
{
public:

	Interfaces::IObject::Type getType() const override;

	bool contact(IObject * object) override;

	bool interact(GameAct::Contours::Line * line) override;

	bool interact(GameAct::Objects::Requires::Spikes * spikes) override;
	bool interact(GameAct::Objects::Requires::Edge * edge) override;

	cocos2d::Rect getBoundingBox() const override;
	
	cocos2d::PhysicsBody * getPhysicsBody() const override;

public:

	void nortify() const override;

public:

	Character(const Contours::KitExpert & kitExpert, cocos2d::Layer * layer);
	~Character();

	void assignView(Interfaces::IViewPort * view);

private:

	std::unordered_set<Interfaces::IViewPort *> _view;

	cocos2d::Layer * _layer;
	cocos2d::Action * _updateAction;
	cocos2d::Action * _followAction;
	spine::SkeletonAnimation * _node;
};

}

}

#endif