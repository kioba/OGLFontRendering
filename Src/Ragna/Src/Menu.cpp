#include "Menu.hpp"
namespace Ragna {

// #############################################################################
// ### Ragna::Menu #############################################################
// #############################################################################
Menu::Menu() :
	Panel(true)
{

}


bool Menu::keyDown(const SDL_KeyboardEvent& key)
{
	bool used = Panel::keyDown(key);

	hide();

	return used;
}

void Menu::show()
{
	Panel::show();

	if (view_layout) {
		view_layout->show();
	}
}


void Menu::hide()
{
	Material::hide();

	if (view_layout) {
		view_layout->hide();
	}
}

} // Ragna namespace
