#ifndef __STR_OBJECT_HPP__
#define __STR_OBJECT_HPP__

#include <RunicFont.hpp>


#ifdef WIN32
	#include <SDL.h>
#else
	#include <SDL2/SDL.h>
#endif

#include <string>
#include <sstream>

#include "Shader.hpp"
#include "Ragna.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>


class RAGNA_API StringObject
{
private: /* variables */
	std::string str_builder;
	Shader shader;

	std::vector<float> vertex_buffer;
	int vert_size;

	GLuint vao;
	glm::vec4 obj_color;

public: /* functions */
	StringObject(std::string str);
	virtual ~StringObject();
	void create();
	void draw(glm::mat4 MVP, glm::mat4 model);
};

#endif // __STR_OBJECT_HPP__
