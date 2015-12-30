#include "RunicGlyph.hpp"

namespace Runic {

GlyphPoint::GlyphPoint() :
	is_end_point{false},
	flag{0}
{
}


GlyphPoint::~GlyphPoint()
{
}


void GlyphPoint::setToEndPoint(bool end_point /*= true*/)
{
	is_end_point = end_point;
}


bool GlyphPoint::isEndPoint() const
{
	return is_end_point;
}


void GlyphPoint::setFlag(uint8_t flags)
{
	flag = flags;
}


bool GlyphPoint::isOnCurve() const
{
	return (flag & flags::onCurve) != 0;
}


bool GlyphPoint::xShortVector() const
{
	return (flag & flags::xShortV) != 0;
}


bool GlyphPoint::yShortVector() const
{
	return (flag & flags::yShortV) != 0;
}


bool GlyphPoint::xIsSame() const
{
	return (flag & flags::xSame) != 0;
}


bool GlyphPoint::xIsPositive() const
{
	return (flag & flags::xSame) != 0;
}


bool GlyphPoint::yIsSame() const
{
	return (flag & flags::ySame) != 0;
}


bool GlyphPoint::yIsPositive() const
{
	return (flag & flags::ySame) != 0;
}

} // Runic namespace
