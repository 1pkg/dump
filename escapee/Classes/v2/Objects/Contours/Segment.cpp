#include "Segment.hpp"
#include "Line.hpp"

namespace Objects
{

namespace Contours
{

void
Segment::attach(std::unique_ptr<Line> & line)
{
	if (_lines.size() && _lines.back()->hollow())
		_lines.pop_back();

	cocos2d::log("%d\n", _lines.size());
	_lines.push_back(std::move(line));
}

void
Segment::remove(Line * line)
{
	auto it = std::remove_if(
		_lines.begin(),
		_lines.end(),
		[line](const std::unique_ptr<Line> & ln)
		{
			return ln.get() == line;
		}
	);
	int a = 10;
	_lines.erase(std::remove_if(
		_lines.begin(),
		_lines.end(),
		[line](const std::unique_ptr<Line> & ln)
		{
			return ln.get() == line;
		}
	), _lines.end());
}

bool
Segment::has(Line * line) const
{
	return std::find_if(
		_lines.begin(),
		_lines.end(),
		[line](const std::unique_ptr<Line> & ln)
		{
			return line == ln.get();
		}
	) != _lines.end();
}

bool
Segment::empty() const
{
	return _lines.empty();
}

std::vector<std::unique_ptr<Line>>::iterator
Segment::begin()
{
	return _lines.begin();
}

std::vector<std::unique_ptr<Line>>::iterator
Segment::end()
{
	return _lines.end();
}

}

}