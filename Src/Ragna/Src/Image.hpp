#ifndef __RAGNA_IMAGE_HPP__
#define __RAGNA_IMAGE_HPP__

#include "Material.hpp"
#include "Ragna.hpp"
#include "Core/Rect.hpp"
#include <string>
#include <vector>
#include <memory>

namespace Ragna {
// #############################################################################
// ### Ragna::Image ############################################################
// #############################################################################

class RAGNA_API Image :
	public Material
{
private: /* variables */
	std::shared_ptr<TextureRect> face;

public: /* functions */
	Image();
	virtual ~Image();

	void setImage(std::string filename);
};


} // Ragna namespace

#endif // __RAGNA_IMAGE_HPP__
