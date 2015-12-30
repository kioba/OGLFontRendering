#ifndef __RUNIC_GLYPH__
#define __RUNIC_GLYPH__

#include <vector>
#include <utility>
#include <cstdint>

#include "Runic.hpp"
#include "RunicTriangulator.hpp"

namespace Runic {

class GlyphPoint;
class RawGlyph;


// #############################################################################
// ### Glyph ###################################################################
// #############################################################################

class RUNIC_API GlyphMetric
{
public: /* variables */
	float x_min;
	float y_min;
	float x_max;
	float y_max;
};


// #############################################################################
// ### Glyph ###################################################################
// #############################################################################

class RUNIC_API Glyph
{
public: /* variables */
	GlyphMetric metric;
	std::vector<Triangle> triangles;
	std::vector<Triangle> bezier;
};


// #############################################################################
// ### RawGlyph ################################################################
// #############################################################################

class RawGlyph
{
public: /* variables */
	int16_t number_of_contours;
	int16_t x_min;
	int16_t y_min;
	int16_t x_max;
	int16_t y_max;
	uint16_t instruction_length;
	std::vector<uint8_t> instructions;
	std::vector<GlyphPoint> points;
};


// #############################################################################
// ### GlyphPoint ##############################################################
// #############################################################################

class RUNIC_API GlyphPoint
{
private: /* variables */
	bool is_end_point;
	uint8_t flag;

public: /* types */
	enum flags {
		onCurve = 1,
		xShortV = 2,
		yShortV = 4,
		repeate = 8, // used when reading font data!
		xSame = 16,
		ySame = 32
	};

	std::pair<float, float> pos;
public: /* functions */
	GlyphPoint();
	virtual ~GlyphPoint();

	void setToEndPoint(bool end_point = true);
	bool isEndPoint() const;

	void setFlag(uint8_t flags);
	bool isOnCurve() const;

	bool xShortVector() const;
	bool yShortVector() const;

	bool xIsSame() const;
	bool yIsSame() const;

	bool xIsPositive() const;
	bool yIsPositive() const;
};

} // Runic namespace

#endif // __RUNIC_GLYPH__
