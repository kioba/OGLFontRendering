#ifndef __RAGNA_RECT_HPP__
#define __RAGNA_RECT_HPP__

#include "Object.hpp"
#include "Ragna.hpp"
#include <cmath>
#include <glm/glm.hpp>
#include <iostream>

namespace Ragna {

// #############################################################################
// ### Ragna::Rect #############################################################
// #############################################################################

class RAGNA_API Rect :
	public Object
{
protected: /* functions */
	int vert_size;
public: /* functions */
	Rect();
	Rect(float x_axis, float y_axis, float width, float height);
	virtual ~Rect();

	virtual void create() override;
	virtual void draw() const override;

	virtual bool isInside(const glm::vec2 point) const override;
};


// #############################################################################
// ### Ragna::TextureRect ######################################################
// #############################################################################

class RAGNA_API TextureRect :
	public Rect
{
private: /* variables */
	GLuint texture;

public: /* functions */
	TextureRect();
	virtual ~TextureRect();

	virtual void draw() const override;
	void setTextureId(const GLuint textureId);
};

} // Ragna namespace

#endif // __RAGNA_RECT_HPP__
