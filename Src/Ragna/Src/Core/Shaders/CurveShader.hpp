#ifndef __RAGNA_CURVESHADER_HPP__
#define __RAGNA_CURVESHADER_HPP__

#include "Ragna.hpp"
#include "Shader.hpp"
#include <GL/glew.h>
#include <string>

namespace Ragna {

// #############################################################################
// ### Ragna::CurveShader ######################################################
// #############################################################################

class RAGNA_API CurveShader :
	public Shader
{
private: /* variables */
	std::string vert_shader;
	std::string frag_shader;

public: /* functions */
	CurveShader();
	virtual ~CurveShader();
};

} // Ragna namespace

#endif // __RAGNA_CURVESHADER_HPP__
