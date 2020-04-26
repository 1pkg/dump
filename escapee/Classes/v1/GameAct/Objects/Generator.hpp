#ifndef __GAME_ACT_OBECTS_GENERATOR_HPP__
#define __GAME_ACT_OBECTS_GENERATOR_HPP__

#include "Interfaces/INoncopyable.hpp"
#include "Interfaces/IObserver.hpp"
#include "Interfaces/IObjectView.hpp"

#include <array>

namespace GameAct
{

namespace Objects
{

class Registry;

class Generator : public Interfaces::INoncopyable, public Interfaces::IObserver
{
public:

	bool handle(const Interfaces::IObserverable * obsable) override;

public:

	Generator(Registry * registry);

	void update();

private:

	std::unique_ptr<Interfaces::IObjectView> create(Interfaces::IObject::Type type) const;
	std::vector<Interfaces::IObject::Type> roll() const;

	Registry * _registry;

	int _bypassing;
	std::array<std::pair<Interfaces::IObject::Type, float>, (size_t)Interfaces::IObject::Type::Non> _odds;
};

}

}

#endif