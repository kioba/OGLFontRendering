#ifndef __RAGNA_GLYPH_HPP__
#define __RAGNA_GLYPH_HPP__

#include "Ragna.hpp"
#include "Object.hpp"
#include <RunicFont.hpp>

namespace Ragna {

class RAGNA_API Glyph :
	public Object
{
private: /* variables */
	int vert_size;
	int pos_bezier_size;
	int neg_bezier_size;

	std::shared_ptr<Shader> bezier_shader;
	std::shared_ptr<Shader> fill_shader;

	Runic::GlyphMetric bbox;
	Runic::Glyph glyph;
	float scale;

public: /* functions */
	Glyph(char char_code);
	virtual ~Glyph();

	virtual void create() override;
	virtual void draw() const override;

	float getGlyphNormWidth() const;
	float getGlyphNormHeight() const;

	float getBBOXHeight() const;

	virtual bool isInside(const glm::vec2 point) const override;

	void setScale(float scale_value);
	float getScale() const;
};

} // Ragna namespace

#endif // __RAGNA_GLYPH_HPP__
