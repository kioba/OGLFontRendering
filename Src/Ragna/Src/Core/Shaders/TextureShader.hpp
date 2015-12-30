#ifndef __RAGNA_TEXTURESHADER_HPP__
#define __RAGNA_TEXTURESHADER_HPP__

#include "Ragna.hpp"
#include "Shader.hpp"
#include <GL/glew.h>
#include <string>

namespace Ragna {

// #############################################################################
// ### Ragna::TextureShader ####################################################
// #############################################################################

class RAGNA_API TextureShader :
	public Shader
{
private: /* variables */
	std::string vert_shader;
	std::string frag_shader;

public: /* functions */
	TextureShader();
	virtual ~TextureShader();
};

} // Ragna namespace

#endif // __RAGNA_TEXTURESHADER_HPP__
