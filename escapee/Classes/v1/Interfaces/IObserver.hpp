#ifndef __INTERFACES_IOBSERVER_HPP__
#define __INTERFACES_IOBSERVER_HPP__

namespace Interfaces
{

class IObserverable;

class IObserver
{
public:

	virtual ~IObserver() =default;

	bool virtual handle(const IObserverable * obsable) = 0;
};

}

#endif