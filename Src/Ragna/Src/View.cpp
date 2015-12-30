#include "View.hpp"

namespace Ragna {

// #############################################################################
// ### Ragna::View #############################################################
// #############################################################################

View::View(bool hide_after_event) :
	do_hide(hide_after_event)
{
}


View::~View()
{
}


void View::resize(const float width, const float height)
{
	Material::resize(width, height);

	// if (view_layout) {
	// 	view_layout->resize(width, height);
	// }
}


void View::move(const float x_axis, const float y_axis)
{
	Material::move(x_axis, y_axis);

	// if (view_layout) {
	// 	view_layout->move(x_axis, y_axis);
	// }

}


void View::draw()
{
	Material::draw();

	if (view_layout) {
		view_layout->draw();
	}
}


void View::setLayout(std::shared_ptr<Layout> layout)
{
	view_layout = layout;
	if (material_face) {
		// pos = material_face->getPos();
		// view_layout->move(pos.x, pos.y);
		// size = material_face->getSize();
		// view_layout->resize(size.x, size.y);
		view_layout->setZOrder(material_face->getZOrder() + 0.001f);
	}

	// layout->rotateX(material_face->getRotateX());
	// layout->rotateY(material_face->getRotateY());
	// layout->rotateZ(material_face->getRotateZ());
}


std::shared_ptr<Layout> View::getLayout() const
{
	return view_layout;
}


void View::show()
{
	Material::show();

//	if (view_layout) {
//		view_layout->show();
//	}
}


void View::hide()
{
	Material::hide();

//	if (view_layout) {
//		view_layout->hide();
//	}
}


bool View::keyDown(const SDL_KeyboardEvent& key)
{
	bool used = false;

	if (view_layout) {
		used = view_layout->keyDown(key);
	}

	if (do_hide) {
		hide();
	}

	return used;
}


bool View::mouseButtonDown(const SDL_MouseButtonEvent& button)
{
	bool used = false;

	if (view_layout) {
		used = view_layout->mouseButtonDown(button);
	}

	if (do_hide) {
		hide();
	}

	return used;
}


bool View::mouseMotion(const SDL_MouseMotionEvent& motion)
{
	bool used = false;

	if (view_layout) {
		used = view_layout->mouseMotion(motion);
	}

	if (do_hide) {
		hide();
	}

	return used;
}


bool View::mouseWheel(const SDL_MouseWheelEvent& wheel)
{
	bool used = false;

	if (view_layout) {
		used = view_layout->mouseWheel(wheel);
	}

	if (do_hide) {
		hide();
	}

	return used;
}


void View::setZOrder(float z_axis)
{
	Material::setZOrder(z_axis);

	if (view_layout) {
		view_layout->setZOrder(z_axis + 0.001f);
	}
}


} // Ragna namespace
