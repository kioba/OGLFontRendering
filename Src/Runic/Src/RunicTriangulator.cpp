#include "RunicTriangulator.hpp"

#include <algorithm>

namespace Runic {

// #############################################################################
// ### Triangulator ############################################################
// #############################################################################

Triangulator::Triangulator()
{
}


Triangulator::~Triangulator()
{
}


// #############################################################################
// ### BasicTri2D ##############################################################
// #############################################################################

BasicTri2D::BasicTri2D()
{
}


BasicTri2D::~BasicTri2D()
{
}


void BasicTri2D::addCounture(const std::vector<std::pair<float, float>>& polyline)
{
	if(polyline.size() < 3) {
		return;
	}

	std::vector<p2t::Point*> cdt_points;
	for (auto IT = polyline.begin(); IT != polyline.end(); ++IT) {
		p2t::Point* point = new p2t::Point(IT->first, IT->second);

		cdt_points.push_back(point);
	}

	std::vector<p2t::Point*>::iterator unique_it;
	unique_it = std::unique(cdt_points.begin(),
							cdt_points.end(),
							[](p2t::Point* p1, p2t::Point* p2) -> bool
							{ return p1->x == p2->x && p1->y == p2->y; });
	cdt_points.resize(std::distance(cdt_points.begin(), unique_it));

	cdt_array.resize(cdt_array.size() + 1);
	cdt_array.back().reset(new p2t::CDT(cdt_points));
}


void BasicTri2D::addHole(const std::vector<std::pair<float, float>>& polyline)
{
	if(polyline.size() < 3) {
		return;
	}

	std::vector<p2t::Point*> hole;
	for (auto IT = polyline.begin(); IT != polyline.end(); ++IT) {
		p2t::Point* point = new p2t::Point(IT->first, IT->second);
		hole.push_back(point);
	}

	cdt_array.back()->AddHole(hole);
}


std::vector<Triangle> BasicTri2D::triangulate()
{
	std::vector<Triangle> temp;
	for (auto IT = cdt_array.begin(); IT != cdt_array.end(); ++IT) {
		(*IT)->Triangulate();

		std::vector<p2t::Triangle*> triangles = (*IT)->GetTriangles();
		for (auto IT_tri = triangles.begin(); IT_tri != triangles.end(); ++IT_tri) {
			p2t::Point& a = *((*IT_tri)->GetPoint(0));
			p2t::Point& b = *((*IT_tri)->GetPoint(1));
			p2t::Point& c = *((*IT_tri)->GetPoint(2));

			std::pair<float, float> tri_point_a;
			std::pair<float, float> tri_point_b;
			std::pair<float, float> tri_point_c;

			tri_point_a.first = static_cast<float>(a.x);
			tri_point_a.second = static_cast<float>(a.y);

			tri_point_b.first = static_cast<float>(b.x);
			tri_point_b.second = static_cast<float>(b.y);

			tri_point_c.first = static_cast<float>(c.x);
			tri_point_c.second = static_cast<float>(c.y);

			Triangle tri(tri_point_a, tri_point_b, tri_point_c);
			tri.setTriangleType(Triangle::filled);
			tri.setCounterClockWise();
			temp.push_back(tri);
		}
	}

	return temp;
}


// #############################################################################
// ### Triangle ################################################################
// #############################################################################

Triangle::Triangle(std::pair<float, float> first, std::pair<float, float> second, std::pair<float, float> third) :
	a {first},
	b {second},
	c {third},
	tri_type{Triangle::filled}
{
}


Triangle::Triangle()
{
}


Triangle::~Triangle()
{
}

void Triangle::setTriangleType(Triangle::TriangleType type)
{
	tri_type = type;
}


Triangle::TriangleType Triangle::getTriangleType() const
{
	return tri_type;
}


void Triangle::setCounterClockWise()
{
	Orientation orient = getOrientation();
	if (orient == cw) {
		// std::swap<std::pair<float, float>> (a, b); // vs13 not working!
		std::pair<float, float> temp = a;
		a = c;
		c = temp;
	}
}


Triangle::Orientation Triangle::getOrientation() const
{
	float detleft = (a.first - c.first) * (b.second - c.second);
	float detright = (a.second - c.second) * (b.first - c.first);
	float val = detleft - detright;
	const double EPSILON = 1e-12;
	if (val > -EPSILON && val < EPSILON) {
		return collinear;
	} else if (val > 0) {
		return ccw;
	}
	return cw;
}


} // Runic namespace
