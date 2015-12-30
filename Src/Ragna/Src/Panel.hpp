#ifndef __RAGNA_PANEL__
#define __RAGNA_PANEL__

#include "Ragna.hpp"

#include "CardLayout.hpp"
#include "Core/Rect.hpp"
#include "View.hpp"
#include <memory>
#include "Core/Molten.hpp"

namespace Ragna {

// #############################################################################
// ### Ragna::Panel ############################################################
// #############################################################################

class RAGNA_API Panel :
	public View
{
private: /* variables */
	std::shared_ptr<Rect> face;
	std::shared_ptr<CardLayout> card;

public: /* functions */
	Panel();
	Panel(bool hide_after_event);
	virtual ~Panel();

	void setDefaultBar();
	void setPanelBar(std::shared_ptr<View> view);
	std::shared_ptr<View> getPanelBar() const;

	void setCentralView(std::shared_ptr<View> view);
	std::shared_ptr<View> getCentralView() const;
};

} // Ragna namespace

#endif // __RAGNA_PANEL__
