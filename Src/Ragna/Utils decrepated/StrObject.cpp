#include "StrObject.hpp"


StringObject::StringObject(std::string str) :
	str_builder(str),
	obj_color{0.0f, 0.0f, 0.0f, 0.25f}
{

}


StringObject::~StringObject()
{
	glDeleteVertexArrays(1, &vao);
}


void StringObject::create()
{
	char* base_path = SDL_GetBasePath();

	if (base_path == nullptr) {
		base_path = SDL_strdup("./");
	}

	std::stringstream str_buff;
	std::cout << base_path << std::endl;
	str_buff << base_path << "Fonts/Roboto-Black.ttf";

	SDL_free(base_path);

	Runic::RFont font(str_buff.str());
	Runic::GlyphMetric bbox = font.getFontBoundingBox();

	for (size_t i = 0; i < str_builder.length(); i++) {
		Runic::Glyph glyph = font.getGlyph(str_builder[i]);

		for (auto IT =  glyph.triangles.begin(); IT != glyph.triangles.end(); ++IT) {

			vertex_buffer.push_back(i * 0.5f + IT->b.first / bbox.x_max);
			vertex_buffer.push_back(((0 - IT->b.second) / bbox.y_max));
			vertex_buffer.push_back(5.0f);

			vertex_buffer.push_back(i * 0.5f + IT->a.first / bbox.x_max);
			vertex_buffer.push_back(((0 - IT->a.second) / bbox.y_max));
			vertex_buffer.push_back(5.0f);

			vertex_buffer.push_back(i * 0.5f + IT->c.first / bbox.x_max);
			vertex_buffer.push_back(((0 - IT->c.second) / bbox.y_max));
			vertex_buffer.push_back(5.0f);
		}

	}

	vert_size = vertex_buffer.size() / 3;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_buffer.size(), &vertex_buffer[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindVertexArray(0);
}


void StringObject::draw(glm::mat4 MVP, glm::mat4 model)
{
	shader.useShader();
	glBindVertexArray(vao);
	glUniformMatrix4fv(shader.getUniformLoc("MVP"), 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(shader.getUniformLoc("translate"), 1, GL_FALSE, &model[0][0]);
	glUniform4f(shader.getUniformLoc("obj_color"), obj_color.r, obj_color.g, obj_color.b, obj_color.a);

	glDrawArrays(GL_TRIANGLES, 0, vert_size);

	glBindVertexArray(0);
}
