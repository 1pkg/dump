#ifndef __TECH_LINE_HPP__
#define __TECH_LINE_HPP__

#include "GameAct/Objects/Object.hpp"

namespace GameAct
{

namespace Tech
{

class Line
	: public Object
{
public:

	void initialize() override;

	std::string getName() const override;

	void setAdditionalParam( std::string additionalParam ) override;

	void runAction( const std::string & action ) override;

private:

	float _rotationTime;

	Direction _direction;
};

}

}

#endif
