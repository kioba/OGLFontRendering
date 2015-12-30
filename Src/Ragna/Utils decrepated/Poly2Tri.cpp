#include "Poly2Tri.hpp"

#include <iostream>

namespace Ragna {

// #############################################################################
// ### Poly2Tri ################################################################
// #############################################################################

Poly2Tri::Poly2Tri()
{
}


Poly2Tri::~Poly2Tri()
{
}


bool Poly2Tri::checkPoints(std::vector<p2t::Point*>& vector)
{
	if (vector.size() < 3) {
		return false;
	}
	// poly2tri allows only unique points!!!
	// remove dupplicates
	std::vector<p2t::Point*>::iterator unique_it;
	unique_it = std::unique(cdt_contour.begin(), cdt_contour.end(),
	 						[](p2t::Point* p1, p2t::Point* p2) -> bool
							{ return p1->x == p2->x && p1->y == p2->y; });

	cdt_contour.resize(std::distance(cdt_contour.begin(), unique_it));

	return true;
}

void Poly2Tri::addCounturePoint(const glm::vec3& vec3)
{
	p2t::Point* point = new p2t::Point(vec3.x, vec3.y);
	cdt_contour.push_back(point);
}


void Poly2Tri::addCounturePoints(const std::vector<glm::vec3>& polyline)
{
	for (auto IT = polyline.begin(); IT != polyline.end(); ++IT) {
		addCounturePoint(*IT);
	}
}


void Poly2Tri::addHolePoint(const glm::vec3& vec3)
{
	p2t::Point* point = new p2t::Point(vec3.x, vec3.y);
	cdt_hole.push_back(point);
}


void Poly2Tri::addHolePoints(const std::vector<glm::vec3>& polyline)
{
	for (auto IT = polyline.begin(); IT != polyline.end(); ++IT) {
		addHolePoint(*IT);
	}
}

void Poly2Tri::triangulate()
{
	if (!checkPoints(cdt_contour)) {
		std::cerr << "Counture points less than 3!" << std::endl;
		return;
	}

	triangulator.reset(new p2t::CDT(cdt_contour));

	if (checkPoints(cdt_hole)) {
		triangulator->AddHole(cdt_hole);
	}

	triangulator->Triangulate();
}


std::vector<float> Poly2Tri::getTrianglesVerts()
{
	std::vector<p2t::Triangle*> triangles = triangulator->GetTriangles();
	std::vector<float> temp;
	for (auto IT_tri = triangles.begin(); IT_tri != triangles.end(); ++IT_tri) {
		p2t::Point& a = *((*IT_tri)->GetPoint(0));
		p2t::Point& b = *((*IT_tri)->GetPoint(1));
		p2t::Point& c = *((*IT_tri)->GetPoint(2));

		temp.push_back(static_cast<float>(a.x));
		temp.push_back(static_cast<float>(a.y));
		temp.push_back(0);

		temp.push_back(static_cast<float>(b.x));
		temp.push_back(static_cast<float>(b.y));
		temp.push_back(0);

		temp.push_back(static_cast<float>(c.x));
		temp.push_back(static_cast<float>(c.y));
		temp.push_back(0);
	}

	return temp;
}

} // Ragna namespace
