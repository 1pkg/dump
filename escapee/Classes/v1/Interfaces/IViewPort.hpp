#ifndef __INTERFACES_IVIEW_PORT_HPP__
#define __INTERFACES_IVIEW_PORT_HPP__

#include "INoncopyable.hpp"
#include "IObserver.hpp"

#include <cocos2d.h>

namespace Interfaces
{

class IViewPort : public INoncopyable, public IObserver
{
public:

	virtual ~IViewPort() =default;

	virtual cocos2d::Rect getBoundingBox() const =0;

	virtual void render() const =0;

	virtual void update(cocos2d::Vec2 delta) =0;
};

}

#endif