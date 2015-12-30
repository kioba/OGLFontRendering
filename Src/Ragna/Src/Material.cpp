#include "Material.hpp"

namespace Ragna {

// #############################################################################
// ### Ragna::Material #########################################################
// #############################################################################

Material::Material() :
	Core(Core::MATERIAL),
	zOrder{0.0f}
{
}


Material::~Material()
{
}


void Material::resize(const float width, const float height)
{
	size.x = width;
	size.y = height;

	if (material_face) {
		material_face->resize(width, height);
	}
}


void Material::move(const float x_axis, const float y_axis)
{
	pos.x = x_axis;
	pos.y = y_axis;

	if (material_face) {
		material_face->move(x_axis, y_axis);
	}
}


void Material::draw()
{
	if (material_face) {
		material_face->draw();
	}
}


void Material::setMaterialFace(std::shared_ptr<Object> face)
{
	material_face = face;
}


std::shared_ptr<Object> Material::getMaterialFace() const
{
	return material_face;
}

bool Material::keyDown(const SDL_KeyboardEvent& /*key*/)
{
	return false;
}


bool Material::mouseButtonDown(const SDL_MouseButtonEvent& button)
{
	if (button.button == SDL_BUTTON_LEFT) {
		glm::vec2 pos = Molten::getInstance().convertToNorm((float)button.x, (float) button.y);
		if (material_face) {
			if (material_face->isInside(pos)) {
				if (event) {
					event->fire();
					return true;
				}
			}
		}
	}

	return false;
}


bool Material::mouseMotion(const SDL_MouseMotionEvent& /*motion*/)
{
	return false;
}


bool Material::mouseWheel(const SDL_MouseWheelEvent& /*wheel*/)
{
	return false;
}


void Material::setZOrder(float z_axis)
{
	zOrder = z_axis;
	if (material_face) {
		material_face->setZOrder(z_axis);
	}
}

float Material::getZOrder()
{
	if (material_face) {
		return material_face->getZOrder();
	}

	return zOrder;
}


void Material::setEvent(std::shared_ptr<Event> event_value)
{
	event = event_value;
}

} // Ragna namespace
