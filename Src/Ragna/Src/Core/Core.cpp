#include "Core.hpp"

namespace Ragna {

// #############################################################################
// ### Ragna::Core #############################################################
// #############################################################################

Core::Core(const UIType type) :
	ui_type{type},
	visible{true},
	pos{0.0f, 0.0f},
	size{0.0f, 0.0f}
{
}


Core::~Core()
{
}


void Core::setType(const UIType type)
{
	ui_type = type;
}


Core::UIType Core::getType() const
{
	return ui_type;
}


void Core::show()
{
	visible = true;
}


void Core::hide()
{
	visible = false;
}


bool Core::isVisible() const
{
	return visible;
}


glm::vec2 Core::getSize() const
{
	return size;
}


glm::vec2 Core::getPos() const
{
	return pos;
}


} // Ragna namespace
