#include "Polygon.hpp"

namespace Ragna {

bool operator==(const PolyPoint& first_point, const PolyPoint& second_point)
{
	return first_point.pos == second_point.pos;
}


Polygon::Polygon()
{
}


Polygon::~Polygon()
{
}

} // Ragna namespace
