#ifndef __OBJECTS_CONTOURS_SEGMENT_HPP__
#define __OBJECTS_CONTOURS_SEGMENT_HPP__

#include "Environment/fwd.hpp"
#include <cocos2d.h>

namespace Objects
{

namespace Contours
{

class Line;
class Segment : public supps::Wrapper
{
public:

	void attach(std::unique_ptr<Line> & line);
	void remove(Line * line);
	bool has(Line * line) const;
	bool empty() const;

	std::vector<std::unique_ptr<Line>>::iterator begin();
	std::vector<std::unique_ptr<Line>>::iterator end();

private:

	std::vector<std::unique_ptr<Line>> _lines;
};

}

}

#endif