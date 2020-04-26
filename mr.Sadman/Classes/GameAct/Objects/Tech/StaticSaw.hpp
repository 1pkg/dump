#ifndef __TECH_STATIC_SAW_HPP__
#define __TECH_STATIC_SAW_HPP__

#include "GameAct/Objects/Object.hpp"
 
/* FINISHED */

namespace GameAct
{

namespace Tech
{

class StaticSaw
	: public Object
{
public:

	std::string getName() const override;
	
	void setAdditionalParam( std::string additionalParam ) override;

	void runAction( const std::string & action ) override;

private:

	float _time;
};

}

}

#endif
