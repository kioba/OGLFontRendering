#ifndef __RUNIC_TRIANGULATOR__
#define __RUNIC_TRIANGULATOR__

#include <utility>
#include <vector>
#include <memory>

#include "Runic.hpp"
#include "../../3thParty/poly2tri/poly2tri/poly2tri.h"

namespace Runic {

class Triangle;

// #############################################################################
// ### Triangulator ############################################################
// #############################################################################

class RUNIC_API Triangulator
{
public:
	Triangulator();
	virtual ~Triangulator();

	virtual void addCounture(const std::vector<std::pair<float, float>>& polyline) = 0;
	virtual void addHole(const std::vector<std::pair<float, float>>& polyline) = 0;

	virtual std::vector<Triangle> triangulate() = 0;
};


// #############################################################################
// ### BasicTri2D ##############################################################
// #############################################################################

class BasicTri2D :
	public Triangulator
{
	std::vector<std::unique_ptr<p2t::CDT>> cdt_array;

public:
	BasicTri2D();
	virtual ~BasicTri2D();

	virtual void addCounture(const std::vector<std::pair<float, float>>& polyline) override;
	virtual void addHole(const std::vector<std::pair<float, float>>& polyline) override;

	virtual std::vector<Triangle> triangulate() override;
};


// #############################################################################
// ### Triangle ################################################################
// #############################################################################

class RUNIC_API Triangle
{
public: /* types */
	enum Orientation
	{
		cw			= 0,
		ccw			= 1,
		collinear	= 2
	};

	enum TriangleType
	{
		filled		= 0,
		positive	= 1,
		negative	= 2
	};

public: /* variables */
	std::pair<float, float> a;
	std::pair<float, float> b;
	std::pair<float, float> c;

	TriangleType tri_type;

public: /* functions */
	Triangle(std::pair<float, float> a, std::pair<float, float> b, std::pair<float, float> c);
	Triangle();
	virtual ~Triangle();

	void setTriangleType(TriangleType type);
	TriangleType getTriangleType() const;

	Orientation getOrientation() const;
	void setCounterClockWise();
};


} // Runic namespace

#endif // __RUNIC_TRIANGULATOR__
