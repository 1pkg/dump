#ifndef __ENVIRONMENT_SUPPORTS_OBSERVERABLE__
#define __ENVIRONMENT_SUPPORTS_OBSERVERABLE__

#include "Wrapper.hpp"
#include <unordered_set>

namespace Environment
{

namespace Supports
{

class Observer;
class Observerable : public Wrapper
{
public:

	void subscribe(Observer * obs);
	void unsubscribe(Observer * obs);
	virtual void nortify() = 0;

protected:

	std::unordered_set<Observer *> _observers;
};

}

}

#endif