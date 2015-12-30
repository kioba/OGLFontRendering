#include "Image.hpp"

#ifdef WIN32
	#include <SDL.h>
#else
	#include <SDL2/SDL.h>
#endif

	#include <SDL_image.h>
namespace Ragna {

// #############################################################################
// ### Ragna::Image ############################################################
// #############################################################################

Image::Image() :
	face(new TextureRect)
{
	setMaterialFace(face);
}


Image::~Image()
{
}


void Image::setImage(std::string filename)
{
	GLuint texture = 0;
	SDL_Surface* surface = IMG_Load(filename.c_str());
	if (surface == nullptr) {
		printf("Error: \"%s\"\n",SDL_GetError());
	} else {
		int mode;
		if (surface->format->BytesPerPixel == 3) { // RGB 24bit
			mode= GL_RGB;
		} else if (surface->format->BytesPerPixel == 4) { // RGBA 32bit
			mode = GL_RGBA;
		} else {
			SDL_FreeSurface(surface);
			return;
		}

		glGenTextures(1,&texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0,
						mode, GL_UNSIGNED_BYTE, surface->pixels);

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

		pos.x = 0.0f;
		pos.y = 0.0f;

		size.x = surface->w * 10.0f;
		size.y =surface->h * 10.0f;

		face->move(pos.x, pos.y);
		face->resize(size.x, size.y);
		face->setTextureId(texture);

		SDL_FreeSurface(surface);
	}
}

} // Ragna namespace
