#include "Layout.hpp"

namespace Ragna {

// #############################################################################
// ### Ragna::Layout ###########################################################
// #############################################################################

Layout::Layout() :
	Core(Core::LAYOUT)
{
}


Layout::~Layout()
{
}


void Layout::resize(const float width, const float height)
{
	size.x = width;
	size.y = height;
}


void Layout::move(const float x_axis, const float y_axis)
{
	pos.x = x_axis;
	pos.y = y_axis;
}


void Layout::draw()
{
}


bool Layout::keyDown(const SDL_KeyboardEvent& /*key*/)
{
	return false;
}


bool Layout::mouseButtonDown(const SDL_MouseButtonEvent& /*button*/)
{
	return false;
}


bool Layout::mouseMotion(const SDL_MouseMotionEvent& /*motion*/)
{
	return false;
}


bool Layout::mouseWheel(const SDL_MouseWheelEvent& /*wheel*/)
{
	return false;
}


void Layout::setZOrder(float /*z_axis*/)
{
}

float Layout::getZOrder()
{
	return 0.0f;
}


} // Ragna namespace
