#include "Object.hpp"

#include <vector>

namespace Ragna {

// #############################################################################
// ### Ragna::Object ###########################################################
// #############################################################################

Object::Object() :
	vao{0},
	vbo{0},
	uv_buffer{0},
	obj_color{1.0f, 0.0f, 0.0f, 0.3f},
	pos{0.0f, 0.0f},
	size{1.0f, 1.0f},
	z_order{0.0f},
	rotate_x{0.0f},
	rotate_y{0.0f},
	rotate_z{0.0f}
{
}


Object::~Object()
{
	if (vao != 0) {
		glDeleteVertexArrays(1, &vao);
	}

	if (vbo != 0) {
		glDeleteBuffers(1, &vbo);
	}

	if (uv_buffer != 0) {
		glDeleteBuffers(1, &uv_buffer);
	}
}


void Object::setColor(const glm::vec4 color)
{
	obj_color = color;
}


glm::vec4 Object::getColor() const
{
	return obj_color;
}


void Object::setShader(std::shared_ptr<Shader> shader_program)
{
	shader = shader_program;
}


std::shared_ptr<Shader> Object::getShader() const
{
	return shader;
}


void Object::move(float x_axis, float y_axis)
{
	pos.x = x_axis;
	pos.y = y_axis;
}


glm::vec2 Object::getPos() const
{
	return pos;
}


void Object::resize(float width, float height)
{
	size.x = width;
	size.y = height;
}


glm::vec2 Object::getSize() const
{
	return size;
}


void Object::setZOrder(float z_axis)
{
	z_order = z_axis;
}


float Object::getZOrder() const
{
	return z_order;
}


void Object::rotateX(float degree)
{
	rotate_x = degree;
}


float Object::getRotateX() const
{
	return rotate_x;
}


void Object::rotateY(float degree)
{
	rotate_y = degree;
}


float Object::getRotateY() const
{
	return rotate_y;
}


void Object::rotateZ(float degree)
{
	rotate_z = degree;
}


float Object::getRotateZ() const
{
	return rotate_z;
}


} // Ragna namespace
