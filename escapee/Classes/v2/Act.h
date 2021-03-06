#ifndef __ACT_HPP__
#define __ACT_HPP__

#include "Environment/fwd.hpp"
#include <cocos2d.h>

class Act : public cocos2d::LayerColor
{
public:

    static cocos2d::Scene* scene();
	CREATE_FUNC(Act);

    virtual bool init();

private:

	void updater(float dt);

	std::unique_ptr<supps::Kit> _contours;
};

#endif
