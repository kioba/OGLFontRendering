#ifndef __ITRIANGULATOR_HPP__
#define __ITRIANGULATOR_HPP__

#include "Ragna.hpp"
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <vector>

namespace Ragna {

// #############################################################################
// ### Triangulator ############################################################
// #############################################################################

class RAGNA_API ITriangulator
{
public:
	ITriangulator();
	virtual ~ITriangulator();

	virtual void addCounturePoint(const glm::vec3& polyline) = 0;
	virtual void addCounturePoints(const std::vector<glm::vec3>& polyline) = 0;
	virtual void addHolePoint(const glm::vec3& polyline) = 0;
	virtual void addHolePoints(const std::vector<glm::vec3>& polyline) = 0;

	virtual void triangulate() = 0;
	virtual std::vector<float> getTrianglesVerts() = 0;
};

} // Ragna namespace


#endif // __ITRIANGULATOR_HPP__
