#ifndef __TECH_CANNON_HPP__
#define __TECH_CANNON_HPP__

#include "GameAct/Objects/Object.hpp"

namespace GameAct
{

class Shell;

namespace Tech
{

class Cannon
	: public Object
{
public:

	std::string getName() const override;

	void setAdditionalParam( std::string additionalParam ) override;
	void setDirection( Direction direction ) override;
	void setRotation( float angle ) override;

	void attachToChunk( Chunk & chunk, int zIndex ) override;

	void runAction( const std::string & action ) override;

private:

	void onFire();

	static cocos2d::Sprite * create();
	static Shell * createShell( const std::string & shell );

	std::string _shell;
	int _zIndex;
};

}

}

#endif
