#ifndef __OBJECTS_CONTOURS_DYE_HPP__
#define __OBJECTS_CONTOURS_DYE_HPP__

#include "Environment/fwd.hpp"
#include <cocos2d.h>

namespace Objects

{
namespace Contours
{

class Dye : public supps::Observerable
{
public:

	Dye(cocos2d::Color4F color, float amount);
	cocos2d::Color4F color() const;
	float get() const;
	void update(float amount);
	bool empty() const;
	void nortify() override;

private:
	
	cocos2d::Color4F _color;
	float _amount;
};

}

}

#endif