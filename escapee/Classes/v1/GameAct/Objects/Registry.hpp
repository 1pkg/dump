#ifndef __GAME_ACT_OBECTS_REGISTRY_HPP__
#define __GAME_ACT_OBECTS_REGISTRY_HPP__

#include "Interfaces/IViewPort.hpp"
#include "Interfaces/IObjectView.hpp"
#include "Generator.hpp"

#include <cocos2d.h>

#include <unordered_set>

namespace GameAct
{

namespace Objects
{

class Interactor;

class Registry : public Interfaces::IViewPort
{
public:

	cocos2d::Rect getBoundingBox() const override;

	void render() const override;

	void update(cocos2d::Vec2 delta) override;

public:

	bool handle(const Interfaces::IObserverable * obsable) override;

public:

	Registry(Interactor * interactor, cocos2d::Layer * layer);
	~Registry();

	Interfaces::IObjectView * findObjectView(cocos2d::PhysicsBody * body) const;

	bool intersect(cocos2d::Rect rect) const;

	friend Generator;
	
private:

	Interactor * _interactor;
	std::unordered_set<std::unique_ptr<Interfaces::IObjectView>> _objects;
	
	Generator generator;

	cocos2d::Layer * _layer;
	cocos2d::EventListenerPhysicsContact * _physicListener;

private:

	struct Contact
	{
		std::pair<Interfaces::IObject *, Interfaces::IObject *> pair;

		Contact(std::pair<Interfaces::IObject *, Interfaces::IObject *> p)
		{
			pair = p;
		}

		bool operator==(const Contact & contact) const
		{
			return (pair.first == contact.pair.first && pair.second == contact.pair.second)
				|| (pair.first == contact.pair.second && pair.second == contact.pair.first);
		}
	};

private:

	Contact find(cocos2d::PhysicsBody * objl, cocos2d::PhysicsBody * objr);

	bool contact(cocos2d::PhysicsBody * objl, cocos2d::PhysicsBody * objr);
	void separate(cocos2d::PhysicsBody * objl, cocos2d::PhysicsBody * objr);

	std::vector<Contact> _contacts;
};

}

}

#endif