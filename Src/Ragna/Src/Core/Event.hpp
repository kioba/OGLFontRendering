#ifndef __RAGNA_EVENT__
#define __RAGNA_EVENT__

#include "Ragna.hpp"

namespace Ragna {

// #############################################################################
// ### Ragna::Event ############################################################
// #############################################################################

class RAGNA_API Event
{
public: /* functions */
	Event();
	~Event();
	virtual void fire() = 0;
};

} // Ragna namespace

#endif // __RAGNA_EVENT__
