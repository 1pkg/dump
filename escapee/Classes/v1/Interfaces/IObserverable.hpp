#ifndef __INTERFACES_IOBSERVERABLE_HPP__
#define __INTERFACES_IOBSERVERABLE_HPP__

#include <unordered_set>

namespace Interfaces
{

class IObserver;

class IObserverable
{
public:

	virtual ~IObserverable() =default;

	void virtual addObserver(IObserver * obs);
	void virtual removeObserver(IObserver * obs);

	void virtual nortify() const = 0;

protected:

	std::unordered_set<IObserver *> _observers;
};

}

#endif