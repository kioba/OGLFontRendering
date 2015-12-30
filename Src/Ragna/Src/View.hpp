#ifndef __RAGNA_VIEW__
#define __RAGNA_VIEW__

#include "Ragna.hpp"
#include "Material.hpp"
#include "Layout.hpp"

namespace Ragna {

// #############################################################################
// ### Ragna::View #############################################################
// #############################################################################

class RAGNA_API View :
	public Material
{
protected: /* variables */
	std::shared_ptr<Layout> view_layout;

	bool do_hide;
public: /* functions */
	View(bool hide_after_event);
	virtual ~View();

	void setLayout(std::shared_ptr<Layout> layout);
	std::shared_ptr<Layout> getLayout() const;

	virtual void resize(const float width, const float height) override;
	virtual void move(const float x_axis, const float y_axis) override;
	virtual void draw() override;

	virtual void show() override;
	virtual void hide() override;

	virtual bool keyDown(const SDL_KeyboardEvent& key) override;
	virtual bool mouseButtonDown(const SDL_MouseButtonEvent& button) override;
	virtual bool mouseMotion(const SDL_MouseMotionEvent& motion) override;
	virtual bool mouseWheel(const SDL_MouseWheelEvent& wheel) override;

	virtual void setZOrder(float z_axis) override;
};

} // Ragna namespace


#endif //__RAGNA_VIEW__
