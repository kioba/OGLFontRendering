#include "Molten.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace Ragna {

// #############################################################################
// ### Ragna::Molten ###########################################################
// #############################################################################

Molten::Molten()
{
	MVPmatrix = ortho * view;
	scale = 0.6f;
	model = glm::mat4(1.0f);


	norm_size.first = 10000.0f;
	norm_size.second = 10000.0f;

	ortho = glm::ortho(0.0f, norm_size.first, norm_size.second, 0.0f, 0.1f, 100.0f);
	// glm::mat4 fustrum = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

	view = glm::lookAt(
		glm::vec3(0.0f, 0.0f, 10.0f),	// the position of your camera, in world space
		glm::vec3(0.0f, 0.0f, 0.0f),	// where you want to look at, in world space
		glm::vec3(0.0f, 1.0f, 0.0f)	 	// probably glm::vec3(0,1,0), but (0,-1,0) would make you looking upside-down, which can be great too
	);

	MVPmatrix = ortho * view;
	// MVPmatrix = fustrum * view * model;
	// MVPmatrix = ortho * view * model;

	resolution.first = 0;
	resolution.second = 0;

	// RunicFont load
	char* base_path = SDL_GetBasePath();

	if (base_path == nullptr) {
		base_path = SDL_strdup("./");
	}

	std::stringstream str_buff;
	std::cout << base_path << std::endl;
	str_buff << base_path << "Data/Roboto-Black.ttf";

	SDL_free(base_path);

	state = 1;
	bez_color = false;

	font.reset(new Runic::RFont(str_buff.str()));
}


Molten::~Molten()
{
}


Molten& Molten::getInstance()
{
	static Molten* singleton = nullptr;

	if (singleton == nullptr) {
		singleton = new Molten;
	}

	return *singleton;
}

glm::mat4 Molten::getModel() const
{
	return model;
}


glm::mat4 Molten::getMVP() const
{
	return MVPmatrix;
}


Runic::Glyph Molten::getGlyph(char char_code) const
{
	return font->getGlyph(char_code);
}


Runic::GlyphMetric Molten::getFontBoundingBox() const
{
	return font->getFontBoundingBox();
}


void Molten::increaseScale()
{
	scale += 0.01f;
}


void Molten::decreaseScale()
{
	scale -= 0.01f;
}


float Molten::getScale() const
{
	return scale;
}


void Molten::setResolution(int width, int height)
{
	resolution.first = width;
	resolution.second = height;
}


std::pair<int, int> Molten::getResolution() const
{
	return resolution;
}


void Molten::setNormalizedWidth(float width)
{
	norm_size.first = width;
}


float Molten::getNormalizedWidth() const
{
	return norm_size.first;
}


void Molten::setNormalizedHeight(float height)
{
	norm_size.second = height;
}


float Molten::getNormalizedHeight() const
{
	return norm_size.second;
}


void Molten::keyDown(const SDL_KeyboardEvent& /*key*/)
{
}


void Molten::mouseButtonDown(const SDL_MouseButtonEvent& button)
{
	bool ret = false;
	std::vector<Core*> temp;

	for (size_t i = 0; i < panels.size(); i++) {
		if (panels[i]->isVisible()) {
			temp.push_back(panels[i]);
		}
	}

	while (temp.size() > 0 && !ret) {
		std::vector<Core*>::iterator iter = std::max_element(temp.begin(), temp.end(), [](Core* a, Core* b) {
			return a->getZOrder() < b->getZOrder();
		});

		if (iter != temp.end()) {
			if ((*iter) != nullptr) {
				ret = (*iter)->mouseButtonDown(button);
				temp.erase(iter);
			}
		} else {
			ret = true;
		}
	}
}


void Molten::mouseMotion(const SDL_MouseMotionEvent& /*motion*/)
{
}


void Molten::mouseWheel(const SDL_MouseWheelEvent& /*wheel*/)
{
}


void Molten::renderScene()
{
	for (size_t i = 0; i < panels.size(); i++) {
		if (panels[i] != nullptr && panels[i]->isVisible()) {
			panels[i]->draw();
		}
	}
}


void Molten::appendSchene(Core* panel)
{
	auto iter = std::find (panels.begin(), panels.end(), panel);

	if (iter == panels.end()) {
		panels.push_back(panel);
	}
}


void Molten::removeSchene(Core* panel)
{
	auto iter = std::find (panels.begin(), panels.end(), panel);
	if (iter != panels.end()) {
		panels.erase(iter);
	}
}


glm::vec2 Molten::convertToNorm(float x, float y) const
{
	glm::vec2 pos;
	pos.x = static_cast<float>(x) / resolution.first * norm_size.first;
	pos.y = static_cast<float>(y) / resolution.second * norm_size.second;

	return pos;
}


void Molten::setState(int state_value)
{
	state = state_value;
}


int Molten::getState()
{
	return state;
}

bool Molten::isBezierColored() const
{
	return bez_color;
}


void Molten::setBezierColored(bool colored)
{
	bez_color = colored;
}



} // Ragna namespace
