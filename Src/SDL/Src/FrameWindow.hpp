#ifndef __FRAMEWINDOW_HPP__
#define __FRAMEWINDOW_HPP__

#include <GL/glew.h>
#include <GL/gl.h>

#ifdef WIN32
	#include <SDL_opengl.h>
	#include <SDL.h>
#else
	#include <SDL2/SDL_opengl.h>
	#include <SDL2/SDL.h>
#endif

#include "SDLCXX.hpp"
#include <fstream>
#include <iostream>
#include <string>

// #############################################################################
// ### FrameWindow #############################################################
// #############################################################################

class SDLCXX_API FrameWindow
{
private: /* variables */
	SDL_Window* m_window;
	SDL_GLContext m_context;
	std::string m_title;

private: /* functions */
	static void	logSDLError(std::ostream& os, const std::string msg);

public: /* functions */
	FrameWindow();
	FrameWindow(std::string title);
	virtual ~FrameWindow();

	bool create();
	void destroy();

	void setDimension(const SDL_Rect& dim);
	SDL_Rect getDimension() const;

	void setTitle(const std::string title);
	std::string	getTitle() const;

	SDL_Window* getWindow() const;
	SDL_GLContext getContext() const;
	void swapContext() const;
};

#endif // __FRAMEWINDOW_HPP__
