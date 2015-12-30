#include "Panel.hpp"

#include <sstream>
#include "Core/Shaders/BasicShader.hpp"
#include "Image.hpp"
#include "Text.hpp"

#ifdef WIN32
	#include <SDL.h>
#else
	#include <SDL2/SDL.h>
#endif

namespace Ragna {

// #############################################################################
// ### Ragna::Panel ############################################################
// #############################################################################
Panel::Panel() :
	View(false),
	face(new Rect(500.0f, 500.0f, 9000.0f, 9000.0f)),
	card(new CardLayout(2, 1))
{
	std::shared_ptr<BasicShader> shader(new BasicShader);
	face->setShader(shader);

	setMaterialFace(face);
	setLayout(card);

	setZOrder(1.0f);
	setDefaultBar();

	Molten::getInstance().appendSchene(this);
}


Panel::Panel(bool hide_after_event) :
	View(hide_after_event),
	face(new Rect(500.0f, 500.0f, 9000.0f, 9000.0f)),
	card(new CardLayout(2, 1))
{
	std::shared_ptr<BasicShader> shader(new BasicShader);
	face->setShader(shader);

	setMaterialFace(face);
	setLayout(card);

	setZOrder(1.0f);
	setDefaultBar();

	Molten::getInstance().appendSchene(this);
}


Panel::~Panel()
{
	Molten::getInstance().removeSchene(this);
}


void Panel::setDefaultBar()
{

}


void Panel::setPanelBar(std::shared_ptr<View> view)
{
	card->addItem(0, 0, view);
	view->setZOrder(face->getZOrder() + 0.0001f);
}


std::shared_ptr<View> Panel::getPanelBar() const
{
	std::shared_ptr<Core> panel_bar = card->getItem(0, 0);
	return std::static_pointer_cast<View>(panel_bar);
}


void Panel::setCentralView(std::shared_ptr<View> view)
{
	card->addItem(1, 0, view);
	view->setZOrder(face->getZOrder() + 0.0001f);
}


std::shared_ptr<View> Panel::getCentralView() const
{
	std::shared_ptr<Core> central = card->getItem(1, 0);
	return std::static_pointer_cast<View>(central);
}

} // Ragna namespace
