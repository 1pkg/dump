#include "Kit.hpp"
#include "Segment.hpp"
#include "Line.hpp"
#include "../Colors/Dye.hpp"
#include "Resources/Constants.hpp"

namespace GameAct
{

namespace Contours
{

void
Segment::nortify() const
{
	for(Interfaces::IObserver * obs : _observers)
		if(obs->handle(this))
			break;
}

bool
Segment::handle(const Interfaces::IObserverable * obsable)
{
	const Line * line = dynamic_cast<const Line *>(obsable);
	if(!line)
		return false;

	_lines.erase(std::remove_if(
		_lines.begin(),
		_lines.end(),
		[line](const std::unique_ptr<Line> & ln)
		{
			return ln.get() == line;
		}
	));

	return true;
}

Segment::Segment(Kit * kit, Colors::Dye & dye)
	: _kit(kit), _dye(dye), _isBlanked(false), _current(nullptr)
{
	addObserver(_kit);
}

Kit *
Segment::getParentKit() const
{
	return _kit;
}

bool
Segment::hasLine(Line * line) const
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
Segment::attachLine(std::unique_ptr<Line> & line)
{
	if(_isBlanked || hasLine(line.get()) || _dye.getAmount() < line->getLenth())
		return false;

	if(_current)
		_current.reset(nullptr);

	if(line->getLenth() < Resources::Constants::LINE_MIN_LENTH)
	{
		line->attachToSegment(this);
		_current.reset(line.release());

		if(_dye.getAmount() < Resources::Constants::DYE_MIN_AMOUNT)
			blank();

		return false;
	}
	else
	{
		_dye.updateAmount(-line->getLenth());

		line->attachToSegment(this);
		line->addObserver(this);

		_lines.push_back(std::move(line));

		return true;
	}
}

void
Segment::blank()
{
	if(_isBlanked || hasLine(_current.get()))
		return;

	if(_current && _dye.getAmount() > _current->getLenth())
	{
		_dye.updateAmount(-_current->getLenth());

		_current->addObserver(this);

		_lines.push_back(std::move(_current));

		_isBlanked = true;
	}

	if(_dye.getAmount() < Resources::Constants::DYE_MIN_AMOUNT)
		_dye.setAmount(0.0f);
}

cocos2d::Color4F
Segment::getColor() const
{
	return _dye.getColor();
}

}

}