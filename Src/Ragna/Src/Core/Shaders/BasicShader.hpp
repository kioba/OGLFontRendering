#ifndef __RAGNA_BASICSHADER_HPP__
#define __RAGNA_BASICSHADER_HPP__

#include "Ragna.hpp"
#include "Shader.hpp"
#include <GL/glew.h>
#include <string>

namespace Ragna {

// #############################################################################
// ### Ragna::BasicShader ######################################################
// #############################################################################

class RAGNA_API BasicShader :
	public Shader
{
private: /* variables */
	std::string vert_shader;
	std::string frag_shader;

public: /* functions */
	BasicShader();
	virtual ~BasicShader();
};

} // Ragna namespace

#endif // __RAGNA_BASICSHADER_HPP__
