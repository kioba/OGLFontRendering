#include "Rect.hpp"

#include "Molten.hpp"
#include "Shaders/BasicShader.hpp"
#include "Shaders/TextureShader.hpp"
#include <vector>

namespace Ragna {

// #############################################################################
// ### Ragna::Rect #############################################################
// #############################################################################

Rect::Rect() :
	vert_size{0}
{
	move(0.0f, 0.0f);
	resize(0.0f, 0.0f);
	create();
}


Rect::Rect(float x_axis, float y_axis, float width, float height) :
	vert_size{0}
{
	move(x_axis, y_axis);
	resize(width, height);
	create();
}


Rect::~Rect()
{
}


void Rect::create()
{
	std::vector<float> vertex_buffer_data = {
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	std::vector<float> uv_buffer_data = {
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f
	};

	vert_size = vertex_buffer_data.size() / 3;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_buffer_data.size(),
	 				&vertex_buffer_data[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glGenBuffers(1, &uv_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * uv_buffer_data.size(),
					&uv_buffer_data[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindVertexArray(0);
}


void Rect::draw() const
{
	glm::mat4 MVP = Molten::getInstance().getMVP();
	glm::mat4 model = Molten::getInstance().getModel();
	// float scal = Molten::getInstance().getScale();
	MVP = MVP * model *	glm::translate(glm::vec3(pos.x, pos.y, z_order)) *
						glm::rotate(rotate_x, glm::vec3(1.0f, 0.0f, 0.0f)) *
						glm::rotate(rotate_y, glm::vec3(0.0f, 1.0f, 0.0f)) *
						glm::rotate(rotate_z, glm::vec3(0.0f, 0.0f, 1.0f)) *
						glm::scale(glm::vec3(size.x, size.y, 0.0f));

	shader->useShader();

	glUniformMatrix4fv(shader->getUniformLoc("MVP"), 1, GL_FALSE, &MVP[0][0]);
	glUniform4f(shader->getUniformLoc("obj_color"), obj_color.r, obj_color.g, obj_color.b, obj_color.a);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vert_size);
	glBindVertexArray(0);
}


bool Rect::isInside(const glm::vec2 point) const
{
	bool inside_x = point.x > pos.x && point.x < (pos.x + size.x);
	bool inside_y = point.y > pos.y && point.y < (pos.y + size.y);

	return inside_x && inside_y;
}


// #############################################################################
// ### Ragna::TextureRect ######################################################
// #############################################################################

TextureRect::TextureRect() :
	Rect(0, 0, 96, 96),
	texture{0}
{
	std::shared_ptr<Shader> shader(new TextureShader);
	setShader(shader);
}


TextureRect::~TextureRect()
{
	if (texture != 0) {
		glDeleteTextures(1, &texture);
	}
}

void TextureRect::setTextureId(const GLuint textureId)
{
	texture = textureId;
}

void TextureRect::draw() const
{
	glm::mat4 MVP = Molten::getInstance().getMVP();
	glm::mat4 model = Molten::getInstance().getModel();
	MVP = MVP * model * glm::translate(glm::vec3(pos.x, pos.y, z_order)) *
						glm::rotate(rotate_x, glm::vec3(1.0f, 0.0f, 0.0f)) *
						glm::rotate(rotate_y, glm::vec3(0.0f, 1.0f, 0.0f)) *
						glm::rotate(rotate_z, glm::vec3(0.0f, 0.0f, 1.0f)) *
						glm::scale(glm::vec3(size.x, size.y, 0.0f));

	shader->useShader();

	glUniformMatrix4fv(shader->getUniformLoc("MVP"), 1, GL_FALSE, &MVP[0][0]);
	glUniform4f(shader->getUniformLoc("obj_color"), 1.0f, 1.0f, 1.0f, 0.3f);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glUniform1i(shader->getUniformLoc("texture_sampler"), 0);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vert_size);
	glBindVertexArray(0);
}


} // Ragna namespace
