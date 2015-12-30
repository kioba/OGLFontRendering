#include "FrameWindow.hpp"

#include <iomanip>

// #############################################################################
// ### FrameWindow #############################################################
// #############################################################################

FrameWindow::FrameWindow() :
	m_window(nullptr),
	m_title("SDL")
{
}


FrameWindow::FrameWindow(std::string title) :
	m_window(nullptr),
	m_title(title)
{
}


FrameWindow::~FrameWindow()
{
	if (m_context != 0) {
		logSDLError(std::cerr,"Context was not destroyed!");
	}

	if (m_window != nullptr) {
		logSDLError(std::cerr,"Window was not destroyed!");
	}
}


bool FrameWindow::create()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		logSDLError(std::cerr, "SDL_Init");
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

	m_window = SDL_CreateWindow(m_title.c_str(),
								100, 100,
								800, 600,
								SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN |
								SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

	if (m_window == nullptr) {
		logSDLError(std::cerr, "Window could not be created!");
		return false;
	}

	m_context = SDL_GL_CreateContext(m_window);

	if (m_context == NULL) {
		logSDLError (std::cerr, "Context could not be created!");
		return false;
	}

	glewExperimental = GL_TRUE;

	/*
	*  If no error is returned from glewInit() it returns 0.
	*  For some reason the return wasn't comparing well to GLEW_OK
	*  but if the value is anything but 0, there's an error.
	*/
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		return false;
	}

// #############################################################################
// ### loging opengl version ###################################################
// #############################################################################

	if(GLEW_VERSION_1_1) {
		std::cout << std::setfill('-') << std::setw(80) << "" << std::endl;
		std::cout << "Graphics Successfully Initialized" << std::endl;
		std::cout << "OpenGL Info" << std::endl;
		std::cout << "    Version: " << glGetString(GL_VERSION) << std::endl;
		std::cout << "     Vendor: " << glGetString(GL_VENDOR) << std::endl;
		std::cout << "   Renderer: " << glGetString(GL_RENDERER) << std::endl;
		std::cout << "    Shading: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
		std::cout << std::setfill('-') << std::setw(80) << "" << std::endl;

		if(!GLEW_ARB_vertex_array_object) {
			std::cout << "ARB_vertex_array_object not available." << std::endl;
			std::cout << std::setfill('-') << std::setw(80) << "" << std::endl;
		}
	} else {
		printf("Unable to get any OpenGL version from GLEW!");
	}

	if (!GLEW_VERSION_3_3) {
		return false;
	}

	return true;
}


void FrameWindow::destroy()
{
	if (m_context != NULL) {
		SDL_GL_DeleteContext (m_context);
		m_context = NULL;
	}

	if (m_window != nullptr) {
		SDL_DestroyWindow (m_window);
		m_window = nullptr;
	}

	SDL_Quit();
}


void FrameWindow::setDimension(const SDL_Rect& dimension)
{
	if (m_window != nullptr) {
		SDL_SetWindowPosition(m_window, dimension.x, dimension.y);
		SDL_SetWindowSize(m_window, dimension.w, dimension.h);
	}
}


SDL_Rect FrameWindow::getDimension() const
{
	SDL_Rect dimension;
	dimension.x = 0;
	dimension.y = 0;
	dimension.w = 0;
	dimension.h = 0;

	if (m_window != nullptr) {
		SDL_GetWindowPosition(m_window, &dimension.x, &dimension.y);
		SDL_GetWindowSize(m_window, &dimension.w, &dimension.h);
	}
	return dimension;
}


inline void FrameWindow::setTitle(const std::string title)
{
	m_title = title;

	if (m_window != nullptr) {
		SDL_SetWindowTitle (m_window, m_title.c_str());
	}
}


inline std::string FrameWindow::getTitle() const
{
	return m_title;
}


inline SDL_Window* FrameWindow::getWindow() const
{
	return m_window;
}


inline SDL_GLContext FrameWindow::getContext() const
{
	return m_context;
}

void FrameWindow::swapContext() const
{
	SDL_GL_SwapWindow(m_window);
}


void FrameWindow::logSDLError(std::ostream& os, const std::string msg)
{
	os << msg << "\n \t error: " << SDL_GetError() << std::endl;
}
