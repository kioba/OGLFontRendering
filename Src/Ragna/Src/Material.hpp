#ifndef __RAGNA_MATERIAL__
#define __RAGNA_MATERIAL__

#include "Core/Core.hpp"
#include "Core/Event.hpp"
#include "Core/Molten.hpp"
#include "Core/Object.hpp"
#include "Ragna.hpp"
#include <memory>

namespace Ragna {

// #############################################################################
// ### Ragna::Material #########################################################
// #############################################################################

class RAGNA_API Material :
	public Core
{
protected: /* variables */
	std::shared_ptr<Object> material_face;
	std::shared_ptr<Event> event;
	float zOrder;

public: /* functions */
	Material();
	virtual ~Material();

	virtual void resize(const float width, const float height) override;
	virtual void move(const float x_axis, const float y_axis) override;
	virtual void draw() override;

	void setMaterialFace(std::shared_ptr<Object> face);
	std::shared_ptr<Object> getMaterialFace() const;

	virtual bool keyDown(const SDL_KeyboardEvent& key) override;
	virtual bool mouseButtonDown(const SDL_MouseButtonEvent& button) override;
	virtual bool mouseMotion(const SDL_MouseMotionEvent& motion) override;
	virtual bool mouseWheel(const SDL_MouseWheelEvent& wheel) override;

	virtual void setZOrder(float z_axis) override;
	virtual float getZOrder() override;

	void setEvent(std::shared_ptr<Event> event_value);
};

} // Ragna namespace

#endif // __RAGNA_MATERIAL__
