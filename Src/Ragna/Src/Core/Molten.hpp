#ifndef __RAGNA_MOLTEN_HPP__
#define __RAGNA_MOLTEN_HPP__

#ifdef WIN32
	#include <SDL.h>
#else
	#include <SDL2/SDL.h>
#endif

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <memory>
#include <algorithm>
#include <utility>
#include <RunicFont.hpp>
#include <Ragna.hpp>
#include "Core.hpp"

namespace Ragna {
class Core;
// #############################################################################
// ### Ragna::Molten ###########################################################
// #############################################################################

class RAGNA_API Molten
{
private: /* variables */
	glm::mat4 model;
	glm::mat4 ortho;
	glm::mat4 view;
	glm::mat4 MVPmatrix;
	float scale;

	std::shared_ptr<Runic::RFont> font;

	std::pair<int, int> resolution;
	std::pair<float, float> norm_size;

	std::vector<Core*> panels;
	int state;
	bool bez_color;
private: /* functions */
	Molten();
	Molten(const Molten& source) = delete;
	Molten& operator=(const Molten& source) = delete;

public: /* functions */
	virtual ~Molten();
	static Molten& getInstance();

	glm::mat4 getModel() const;
	glm::mat4 getMVP() const;

	Runic::GlyphMetric getFontBoundingBox() const;
	Runic::Glyph getGlyph(char char_code) const;

	void increaseScale();
	void decreaseScale();
	float getScale() const;

	void setResolution(int width, int height);
	std::pair<int, int> getResolution() const;

	void setNormalizedWidth(float width);
	float getNormalizedWidth() const;

	void setNormalizedHeight(float height);
	float getNormalizedHeight() const;

	void keyDown(const SDL_KeyboardEvent& key);
	void mouseButtonDown(const SDL_MouseButtonEvent& button);
	void mouseMotion(const SDL_MouseMotionEvent& motion);
	void mouseWheel(const SDL_MouseWheelEvent& wheel);

	void renderScene();
	void appendSchene(Core* panel);
	void removeSchene(Core* panel);

	glm::vec2 convertToNorm(float x, float y) const;

	void setState(int state_value);
	int getState();

	bool isBezierColored() const;
	void setBezierColored(bool colored);
};

} // Ragna namespace

#endif // __RAGNA_MOLTEN_HPP__
