#ifndef __RAGNA_OBJECT_HPP__
#define __RAGNA_OBJECT_HPP__

#include "Ragna.hpp"
#include "Shaders/Shader.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/mat4x4.hpp>
#include <memory>

namespace Ragna {

// #############################################################################
// ### Ragna::Object ###########################################################
// #############################################################################

class RAGNA_API Object
{
protected: /* variables */
	GLuint vao;
	GLuint vbo;
	GLuint uv_buffer;

	std::shared_ptr<Shader> shader;
	glm::vec4 obj_color;

	glm::vec2 pos;
	glm::vec2 size;
	float z_order;
	float rotate_x;
	float rotate_y;
	float rotate_z;

public: /* functions */
	Object();
	virtual ~Object();

	void setColor(const glm::vec4 color);
	glm::vec4 getColor() const;

	void setShader(std::shared_ptr<Shader> shader);
	std::shared_ptr<Shader> getShader() const;

	virtual void create() = 0;
	virtual void draw() const = 0;

	virtual bool isInside(const glm::vec2 point) const = 0;

	void move(float x_axis, float y_axis);
	glm::vec2 getPos() const;

	void resize(float width, float height);
	glm::vec2 getSize() const;

	void setZOrder(float z_axis);
	float getZOrder() const;

	void rotateX(float degree);
	float getRotateX() const;

	void rotateY(float degree);
	float getRotateY() const;

	void rotateZ(float degree);
	float getRotateZ() const;
};

} // Ragna namespace

#endif // __RAGNA_OBJECT_HPP__
