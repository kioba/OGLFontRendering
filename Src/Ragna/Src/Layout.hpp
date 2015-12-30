#ifndef __RAGNA_LAYOUT__
#define __RAGNA_LAYOUT__

#include "Ragna.hpp"
#include "Core/Core.hpp"
#include <memory>
#include <utility>
#include <vector>

namespace Ragna {

// #############################################################################
// ### Ragna::Layout ###########################################################
// #############################################################################

class RAGNA_API Layout :
	public Core
{
public: /* functions */
	Layout();
	virtual ~Layout();

	virtual void resize(const float width, const float height) override;
	virtual void move(const float x_axis, const float y_axis) override;
	virtual void draw() override;

	virtual bool keyDown(const SDL_KeyboardEvent& key) override;
	virtual bool mouseButtonDown(const SDL_MouseButtonEvent& button) override;
	virtual bool mouseMotion(const SDL_MouseMotionEvent& motion) override;
	virtual bool mouseWheel(const SDL_MouseWheelEvent& wheel) override;

	virtual void setZOrder(float z_axis) override;
	virtual float getZOrder() override;
};

} // Ragna namespace

#endif // __RAGNA_LAYOUT__
