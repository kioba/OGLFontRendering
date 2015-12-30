#ifndef __RAGNA_SHADER_HPP__
#define __RAGNA_SHADER_HPP__

#include "Ragna.hpp"
#include <GL/glew.h>
#include <string>

namespace Ragna {

class RAGNA_API Shader {
protected: /* variables */
	GLuint programID;

public: /* functions */
	Shader();
	virtual ~Shader();

	void useShader() const;
	GLuint getUniformLoc(std::string name) const;

	bool checkShader(const GLuint shaderId) const;
	void compileShaders(const std::string VertexShaderCode,
						const std::string FragmentShaderCode);
};

} // Ragna namespace

#endif // __RAGNA_SHADER_HPP__
