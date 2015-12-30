#ifndef __RAGNA_POLYGON_HPP__
#define __RAGNA_POLYGON_HPP__

#include <glm/glm.hpp>


namespace Ragna {

// #############################################################################
// ### Ragna::PolyPoint ########################################################
// #############################################################################

class RAGNA_API PolyPoint
{
public: /* variables */
	glm::vec3 pos;
};

bool RAGNA_API operator==(const PolyPoint& first_point, const PolyPoint& second_point);


// #############################################################################
// ### Ragna::Poly #############################################################
// #############################################################################

class RAGNA_API Poly
{
protected: /* functions */
	std::vector<float> triangluate(ITriangulator* triangulator = nullptr);

public: /* functions */
	Polygon();
	virtual ~Polygon();

	virtual void move(float x_axis, float y_axis) = 0;
	virtual void resize(float width, float height) = 0;
	virtual void draw() = 0;
};

} // Ragna namespace


#endif // __RAGNA_POLYGON_HPP__
