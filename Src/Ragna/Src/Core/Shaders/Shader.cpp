#include "Shader.hpp"

#include <iostream>
#include <vector>

namespace Ragna {

Shader::Shader() :
	programID{0}
{
}


Shader::~Shader()
{
	if (programID != 0) {
		glDeleteProgram(programID);
	}
}


void Shader::useShader() const
{
	glUseProgram(programID);
}


GLuint Shader::getUniformLoc(std::string name) const
{
	return glGetUniformLocation(programID, name.c_str());
}


bool Shader::checkShader(const GLuint shaderId) const
{
	GLint err = GL_FALSE;
	int InfoLogLength = 0;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &err);

	if (err == GL_FALSE) {
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength != 0) {
			std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
			glGetShaderInfoLog(shaderId, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
			fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);
		}
	}

	return (err != GL_FALSE);
}


void Shader::compileShaders(const std::string VertexShaderCode,
							const std::string FragmentShaderCode)
{
	GLint Result = GL_FALSE;

	glGetIntegerv(GL_SHADER_COMPILER, &Result);
	if (Result == GL_FALSE) {
		return;
	}

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Compile Vertex Shader
	std::cout << "Compiling Vertex shader" << std::endl;
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	checkShader(VertexShaderID);

	// Compile Fragment Shader
	std::cout << "Compiling Fragment shader" << std::endl;
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	checkShader(FragmentShaderID);

	// Link the program
	std::cout << "Linking program\n" << std::endl;
	programID = glCreateProgram();
	glAttachShader(programID, VertexShaderID);
	glAttachShader(programID, FragmentShaderID);
	glLinkProgram(programID);

	// Check the program
	int InfoLogLength = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, &Result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength != 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength);
		glGetProgramInfoLog(programID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
	}

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
}

} // Ragna namespace
