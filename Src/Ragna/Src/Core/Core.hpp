#ifndef __RAGNA_CORE__
#define __RAGNA_CORE__

#ifdef WIN32
	#include <SDL.h>
#else
	#include <SDL2/SDL.h>
#endif

#include "Ragna.hpp"
#include <glm/glm.hpp>
#include <utility>

namespace Ragna {

// #############################################################################
// ### Ragna::Core #############################################################
// #############################################################################

class RAGNA_API Core
{
protected: /* types */
	enum UIType {
		LAYOUT		= 0,
		MATERIAL	= 1
	};

protected: /* variables */
	UIType ui_type;
	bool visible;

	glm::vec2 pos;
	glm::vec2 size;

protected: /* functions */
	Core(const UIType type);
	virtual ~Core();

	void setType(const UIType type);
	UIType getType() const;

public: /* functions */
	virtual void show();
	virtual void hide();

	bool isVisible() const;

	virtual void setZOrder(float z_axis) = 0;
	virtual float getZOrder() = 0;

	virtual glm::vec2 getSize() const;
	virtual glm::vec2 getPos() const;

	virtual void resize(const float width, const float height) = 0;
	virtual void move(const float x_axis, const float y_axis) = 0;
	virtual void draw() = 0;

	virtual bool keyDown(const SDL_KeyboardEvent& key) = 0;
	virtual bool mouseButtonDown(const SDL_MouseButtonEvent& button) = 0;
	virtual bool mouseMotion(const SDL_MouseMotionEvent& motion) = 0;
	virtual bool mouseWheel(const SDL_MouseWheelEvent& wheel) = 0;
};

} // Ragna namespace

#endif // __RAGNA_CORE__
