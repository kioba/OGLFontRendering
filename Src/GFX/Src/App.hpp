#ifndef APP_H
#define APP_H

// #define GLM_FORCE_CXX11
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>

#include <FrameWindow.hpp>
#include <iostream>
#include <memory>
#include <Panel.hpp>
#include <Menu.hpp>
#include <View.hpp>
#include <Core/Shaders/BasicShader.hpp>
#include <Text.hpp>
#include <Image.hpp>
#include <CardLayout.hpp>
#include <Core/Rect.hpp>
#include <Core/Event.hpp>

class BackEvent :
	public Ragna::Event
{
public:
	virtual void fire() override
	{
		int state = Ragna::Molten::getInstance().getState();
		if (state == 1) {
			state = 3;
		} else {
			--state;
		}

		Ragna::Molten::getInstance().setState(state);
	}
};


class ForwEvent :
	public Ragna::Event
{
public:
	virtual void fire() override
	{
		int state = Ragna::Molten::getInstance().getState();
		if (state == 3) {
			state = 1;
		} else {
			++state;
		}

		Ragna::Molten::getInstance().setState(state);
	}
};


class ScaleEvent :
	public Ragna::Event
{
private:
	std::shared_ptr<bool> scale;
public:
	ScaleEvent(std::shared_ptr<bool> scale_value)
	{
		scale = scale_value;
	}

	virtual void fire() override
	{
		if (scale) {
			*scale = !(*scale);
		}
	}
};


class MenuEvent :
	public Ragna::Event
{
private:
	std::shared_ptr<Ragna::Menu> menu_item;
public:
	MenuEvent(std::shared_ptr<Ragna::Menu> menu)
	{
		menu_item = menu;
	}

	virtual void fire() override
	{
		if (menu_item) {
			menu_item->show();
		}
	}
};


class BezierEvent :
	public Ragna::Event
{
public:
	virtual void fire() override
	{
		bool colored = Ragna::Molten::getInstance().isBezierColored();
		Ragna::Molten::getInstance().setBezierColored(!colored);
	}
};

class App
{
private: /*variables*/
	static App* singleton;
	bool quit;
	FrameWindow window;

	std::shared_ptr<Ragna::Panel> panel;
	std::shared_ptr<Ragna::Menu> menu;

	//shadow
	glm::mat4 depthMVP;
	GLuint FramebufferName;
	GLuint depthTexture;
	int laststate;

	// header
	std::shared_ptr<Ragna::View> header_view;
	std::shared_ptr<Ragna::CardLayout> header;
	std::shared_ptr<Ragna::BasicShader> shader;
	std::shared_ptr<Ragna::Rect> header_rect;

	// header items
	std::shared_ptr<Ragna::Image> left_img;
	std::shared_ptr<Ragna::Text> header_text;
	std::shared_ptr<Ragna::Image> menu_img;
	std::shared_ptr<Ragna::Image> right_img;

	// central
	std::shared_ptr<Ragna::View> central_view;
	std::shared_ptr<Ragna::CardLayout> central;
	std::shared_ptr<Ragna::BasicShader> shader_central;
	std::shared_ptr<Ragna::Rect> rect_face;

	// central items
	std::shared_ptr<Ragna::Text> first_scene;
	std::shared_ptr<Ragna::Text> second_scene;
	std::shared_ptr<Ragna::Text> third_scene;
	std::shared_ptr<Ragna::BasicShader> third_scene_shader;
	std::shared_ptr<Ragna::Rect> third_scene_face;

	// menu

	std::shared_ptr<Ragna::View> menu_view;
	std::shared_ptr<Ragna::CardLayout> menu_layout;
	std::shared_ptr<Ragna::BasicShader> shader_menu;
	std::shared_ptr<Ragna::Rect> menu_face;



	std::shared_ptr<Ragna::Text> text_scale;
	std::shared_ptr<Ragna::BasicShader> scale_shader;
	std::shared_ptr<Ragna::Rect> scale_face;

	std::shared_ptr<Ragna::Text> text_bezier;
	std::shared_ptr<Ragna::BasicShader> bezier_shader;
	std::shared_ptr<Ragna::Rect> bezier_face;


	std::shared_ptr<bool> scale;

	const std::string basic_text;
	float curr_scale;

	unsigned int lastTic;
private: /*functions*/
	App();
	App(const App& other) = delete;
	App& operator=(const App& other) = delete;

	bool init();
	void cleanUp();
	void update();
	void render();

	bool createShadowMap();

	void handleInput();
	void keyDownEvent(const SDL_KeyboardEvent& key);
	void mouseButtonDownEvent(const SDL_MouseButtonEvent& button);
	void mouseMotionEvent(const SDL_MouseMotionEvent& motion);
	void mouseWheelEvent(const SDL_MouseWheelEvent& wheel);
	void windowEvent(const SDL_WindowEvent& window);

public: /*functions*/
	static App& getSingleton();
	~App();

	void execute();
};


#endif // APP_H
