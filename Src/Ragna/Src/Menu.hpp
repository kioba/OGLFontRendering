#ifndef __RAGNA_MENU__
#define __RAGNA_MENU__

#include "Panel.hpp"
#include "Ragna.hpp"

namespace Ragna {

// #############################################################################
// ### Ragna::Menu #############################################################
// #############################################################################

class RAGNA_API Menu :
	public Panel
{
public: /* functions */
	Menu();
	virtual bool keyDown(const SDL_KeyboardEvent& key) override;

	virtual void show() override;
	virtual void hide() override;
};

} // Ragna namespace

#endif // __RAGNA_MENU__
