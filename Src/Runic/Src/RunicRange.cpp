#include "RunicRange.hpp"

namespace RunicCore {

// #############################################################################
// ### RRange ##################################################################
// #############################################################################

RRange::RRange(RRange::Iter begin_pos, RRange::Iter end_pos) :
	front(begin_pos),
	back(end_pos)
{
}


RRange::RRange()
{
}


RRange::~RRange()
{
}


RRange::Iter RRange::begin() const
{
	return front;
}


void RRange::setBegin(RRange::Iter iter)
{
	front = iter;
}


RRange::Iter RRange::end() const
{
	return back;
}


void RRange::setEnd(RRange::Iter iter)
{
	back = iter;
}


unsigned int RRange::getSize() const
{
	return back - front;
}


} // RunicCore namespace
