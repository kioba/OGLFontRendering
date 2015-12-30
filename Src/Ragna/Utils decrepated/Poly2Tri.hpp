#ifndef __POLY_2_TRI_HPP__
#define __POLY_2_TRI_HPP__

#include <memory>
#include <algorithm>

#include <poly2tri.h>
#include <glm/glm.hpp>
#include <glm/vec2.hpp>

#include "ITriangulator.hpp"

namespace Ragna {

// #############################################################################
// ### Poly2Tri ################################################################
// #############################################################################

class Poly2Tri :
	public ITriangulator
{
private: /* variables */
	std::unique_ptr<p2t::CDT> triangulator;

	std::vector<p2t::Point*> cdt_contour;
	std::vector<p2t::Point*> cdt_hole;

	bool checkPoints(std::vector<p2t::Point*>& vector);
public: /* functions */
	Poly2Tri();
	virtual ~Poly2Tri();

	virtual void addCounturePoint(const glm::vec3& polyline) override;
	virtual void addCounturePoints(const std::vector<glm::vec3>& polyline) override;
	virtual void addHolePoint(const glm::vec3& polyline) override;
	virtual void addHolePoints(const std::vector<glm::vec3>& polyline) override;

	virtual void triangulate() override;
	virtual std::vector<float> getTrianglesVerts() override;
};

} // Ragna namespace


#endif // __POLY_2_TRI_HPP__
