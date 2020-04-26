#ifndef __GAME_ACT_PHYSICAL_PRESS_HPP__
#define __GAME_ACT_PHYSICAL_PRESS_HPP__

#include "GameAct/Objects/SubTypes/CompositeObject.hpp"

namespace GameAct
{

namespace Physical
{

class Press
	: public CompositeObject
{
public:
	
	Press();

	std::string getResourcesName() const override;

	void setPosition( cocos2d::Vec2 position ) override;
	void setSize( cocos2d::Size size ) override;
	void setAdditionalParam( std::string additionalParam ) override;
	void setRotation( float angle ) override;

	void hide() override;
	void show() override;

	void attachToChunk( Chunk & chunk, int zIndex ) override;

private:

	float _angle;

	Object * _ram;
	Object * _pushPlate;
};

}

}

#endif
