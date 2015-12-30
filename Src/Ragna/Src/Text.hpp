#ifndef __RAGNA_TEXT_HPP__
#define __RAGNA_TEXT_HPP__

#include "Core/Glyph.hpp"
#include "Material.hpp"
#include "Ragna.hpp"
#include "Core/Molten.hpp"
#include <memory>
#include <string>

#ifdef WIN32
	#include <SDL.h>
#else
	#include <SDL2/SDL.h>
#endif

namespace Ragna {

// #############################################################################
// ### Ragna::Text #############################################################
// #############################################################################

class RAGNA_API Text :
	public Material
{
private: /* variables */
	std::vector<std::shared_ptr<Glyph>> char_objects;
	std::string characters;
	float scale;

public: /* functions */
	Text();
	virtual ~Text();

	void setText(std::string text);
	std::string getText() const;

	virtual void draw() override;

	void setScale(float scale_value);
	float getScale() const;

	float getWidth() const;
	float getHeight() const;

	virtual void setZOrder(float z_axis) override;
};


} // Ragna namespace

#endif // __RAGNA_TEXT_HPP__
