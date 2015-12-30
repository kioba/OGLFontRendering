#include "Glyph.hpp"
#include "Shaders/CurveShader.hpp"
#include "Shaders/BasicShader.hpp"
#include "Molten.hpp"

#include <vector>

namespace Ragna {

Glyph::Glyph(char char_code) :
	vert_size{0},
	pos_bezier_size{0},
	neg_bezier_size{0},
	scale{0.2f}

{
	bezier_shader.reset(new CurveShader);
	fill_shader.reset(new BasicShader);
	bbox = Molten::getInstance().getFontBoundingBox();
	glyph = Molten::getInstance().getGlyph(char_code);
	create();
}


Glyph::~Glyph()
{
}


void Glyph::create()
{
	std::vector<float> vertex_buffer_data;
	std::vector<float> uv_buffer_data;

	for (auto IT = glyph.triangles.begin(); IT != glyph.triangles.end(); ++IT) {
		// vertex coordinates
		vertex_buffer_data.push_back(IT->b.first);
		vertex_buffer_data.push_back((0 - IT->b.second));
		vertex_buffer_data.push_back(5.0f);

		vertex_buffer_data.push_back(IT->a.first);
		vertex_buffer_data.push_back((0 - IT->a.second));
		vertex_buffer_data.push_back(5.0f);

		vertex_buffer_data.push_back(IT->c.first);
		vertex_buffer_data.push_back((0 - IT->c.second));
		vertex_buffer_data.push_back(5.0f);

		// UV coordinates for each vertex
		uv_buffer_data.push_back(0.5f);
		uv_buffer_data.push_back(0.0f);

		uv_buffer_data.push_back(1.0f);
		uv_buffer_data.push_back(1.0f);

		uv_buffer_data.push_back(0.0f);
		uv_buffer_data.push_back(0.0f);

		vert_size += 3;
	}

	std::vector<float> pos_bezier_data;
	std::vector<float> neg_bezier_data;

	for (auto IT = glyph.bezier.begin(); IT != glyph.bezier.end(); ++IT) {
		std::vector<float>* temp = nullptr;

		if (IT->getTriangleType() == Runic::Triangle::positive) {
			temp = &pos_bezier_data;
			pos_bezier_size += 3;
		} else if (IT->getTriangleType() == Runic::Triangle::negative) {
			temp = &neg_bezier_data;
			neg_bezier_size += 3;
		} else {
			continue;
		}

		temp->push_back(IT->b.first);
		temp->push_back((0 - IT->b.second));
		temp->push_back(5.1f);

		temp->push_back(IT->a.first);
		temp->push_back((0 - IT->a.second));
		temp->push_back(5.1f);

		temp->push_back(IT->c.first);
		temp->push_back((0 - IT->c.second));
		temp->push_back(5.1f);

		// UV coordinates for each vertex
		uv_buffer_data.push_back(0.5f);
		uv_buffer_data.push_back(0.0f);

		uv_buffer_data.push_back(1.0f);
		uv_buffer_data.push_back(1.0f);

		uv_buffer_data.push_back(0.0f);
		uv_buffer_data.push_back(0.0f);
	}

	vertex_buffer_data.insert(vertex_buffer_data.end(),
								pos_bezier_data.begin(),
								pos_bezier_data.end());

	vertex_buffer_data.insert(vertex_buffer_data.end(),
								neg_bezier_data.begin(),
								neg_bezier_data.end());

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


void Glyph::draw() const
{
	glm::mat4 MVP = Molten::getInstance().getMVP();
	glm::mat4 model = Molten::getInstance().getModel();
	MVP = MVP * model *	glm::translate(glm::vec3(pos.x, pos.y, z_order)) *
						glm::rotate(rotate_x, glm::vec3(1.0f, 0.0f, 0.0f)) *
						glm::rotate(rotate_y, glm::vec3(0.0f, 1.0f, 0.0f)) *
						glm::rotate(rotate_z, glm::vec3(0.0f, 0.0f, 1.0f)) *
						glm::scale(glm::vec3(size.x * scale, size.y * scale, 0.0f));

	glBindVertexArray(vao);

	// filled triangles
	fill_shader->useShader();

	glUniformMatrix4fv(fill_shader->getUniformLoc("MVP"), 1, GL_FALSE, &MVP[0][0]);
	glUniform4f(fill_shader->getUniformLoc("obj_color"), 0.0f, 0.0f, 0.0f, 1.0f);

	glDrawArrays(GL_TRIANGLES, 0, vert_size);

	// bezier curves
	bezier_shader->useShader();

	glUniformMatrix4fv(bezier_shader->getUniformLoc("MVP"), 1, GL_FALSE, &MVP[0][0]);
	glUniform1i(bezier_shader->getUniformLoc("is_positive_arc"), true);
	 if (Molten::getInstance().isBezierColored()) {
		 glUniform4f(bezier_shader->getUniformLoc("obj_color"), 0.0f, 1.0f, 0.0f, 1.0f);
	} else {
		glUniform4f(bezier_shader->getUniformLoc("obj_color"),  0.0f, 0.0f, 0.0f, 1.0f);
	}

	glDrawArrays(GL_TRIANGLES, vert_size, pos_bezier_size);

	glUniform1i(bezier_shader->getUniformLoc("is_positive_arc"), false);

	if (Molten::getInstance().isBezierColored()) {
		glUniform4f(bezier_shader->getUniformLoc("obj_color"), 0.0f, 0.0f, 1.0f, 1.0f);
	} else {
		glUniform4f(bezier_shader->getUniformLoc("obj_color"),  0.0f, 0.0f, 0.0f, 1.0f);
	}

	glDrawArrays(GL_TRIANGLES, vert_size + pos_bezier_size, neg_bezier_size);

	glBindVertexArray(0);
}


bool Glyph::isInside(const glm::vec2 /*point*/) const
{
	return true;
}


float Glyph::getGlyphNormWidth() const
{
	float size = std::abs(glyph.metric.x_max - glyph.metric.x_min);
	return size;
}


float Glyph::getGlyphNormHeight() const
{

	return std::abs(glyph.metric.y_max - glyph.metric.y_min);
}


float Glyph::getBBOXHeight() const
{
	return std::abs(bbox.y_max);
}



void Glyph::setScale(float scale_value)
{
	scale = scale_value;
}


float Glyph::getScale() const
{
	return scale;
}


} // Ragna namespace
