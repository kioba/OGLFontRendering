#include "Text.hpp"


namespace Ragna {

// #############################################################################
// ### Ragna::Text #############################################################
// #############################################################################

Text::Text() :
	scale{0.5f}
{
	std::shared_ptr<Glyph> ptr(new Glyph('S'));
	ptr->setScale(scale);
	char_objects.push_back(ptr);
}


Text::~Text()
{
}


void Text::setText(std::string text)
{
	characters = text;
	char_objects.clear();
	std::shared_ptr<Glyph> ptr;
	for (size_t i = 0; i < characters.length(); ++i) {
		ptr.reset(new Glyph(characters[i]));
		ptr->setScale(scale);
		ptr->setZOrder(getZOrder() + 0.1f);
		char_objects.push_back(ptr);
	}
}


std::string Text::getText() const
{
	return characters;
}


void Text::draw()
{
	Material::draw();
	// float kerning_stepps = 0.05f;
	float kerning = pos.x;

	// unsigned int lastTime = 0;
	//float curr_time = (SDL_GetTicks()) * (360.0f / 1000000.0f);

	for (size_t i = 0; i < char_objects.size(); ++i) {
		if (characters[i] == ' ') {
			kerning += 800.0f * scale;
		} else if (char_objects[i]) {
			char_objects[i]->move(kerning, pos.y + (char_objects[i]->getBBOXHeight() / 3));
			//char_objects[i]->rotateZ(curr_time);
			char_objects[i]->draw();
			float kern_stepp = char_objects[i]->getGlyphNormWidth();

			if (kern_stepp < 1000.0f) {
				kern_stepp += 400.0f;
			}
			kern_stepp += 300.0f;
			kern_stepp *= scale;
			kerning += kern_stepp;
		}
	}
}


void Text::setScale(float scale_value)
{
	scale = scale_value;
	for (size_t i = 0; i < char_objects.size(); ++i) {
		char_objects[i]->setScale(scale);
	}
}


float Text::getScale() const
{
	return scale;
}


void Text::setZOrder(float z_axis)
{
	Material::setZOrder(z_axis + 0.0001f);
	for (size_t i = 0; i < char_objects.size(); ++i) {
		if (char_objects[i]) {
			char_objects[i]->setZOrder(z_axis + 0.0005f);
		}
	}
}


float Text::getWidth() const
{
	float width = 0;
	for (size_t i = 0; i < char_objects.size(); ++i) {
		if (characters[i] == ' ') {
			width += 800.0f * scale;
		} else if (char_objects[i]) {
			float kern_stepp = char_objects[i]->getGlyphNormWidth();

			if (kern_stepp < 1000.0f) {
				kern_stepp += 400.0f;
			}
			kern_stepp += 200.0f;
			kern_stepp *= scale;
			width += kern_stepp;
		}
	}

	return width;
}


float Text::getHeight() const
{
	for (size_t i = 0; i < char_objects.size(); ++i) {
		if (char_objects[i]) {
			return (char_objects[i]->getBBOXHeight() / 3);
		}
	}
	return 0.0f;
}

} // Ragna namespace
