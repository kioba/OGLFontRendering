#include "App.hpp"

#include <Core/Molten.hpp>
#include <algorithm>

App* App::singleton = nullptr;

App::App() :
	quit{false},
	FramebufferName{0},
	depthTexture{0},
	basic_text("Type some text!"),
	curr_scale(-4.0)
{
}


App::~App()
{
}


App& App::getSingleton()
{
	if (singleton == nullptr) {
		singleton = new App;
	}

	return *singleton;
}


bool App::createShadowMap()
{
	// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

	// Depth texture. Slower than a depth buffer, but you can sample it later in your shader
	//GLuint depthTexture;
	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);

	glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT16, 1024, 1024, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);

	glDrawBuffer(GL_NONE); // No color buffer is drawn to.

	// Always check that our framebuffer is ok
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return false;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return true;
}


void App::execute()
{
	if (!init()) {
		cleanUp();
		return;
	}

	while (!quit) {
		handleInput();
		update();
		render();
	}

	cleanUp();
}


bool App::init()
{
	if (glewInit() == 0) {
		return false;
	}

	if (!window.create()) {
		return false;
	}

	SDL_Rect rect = window.getDimension();
	Ragna::Molten::getInstance().setResolution(rect.w, rect.h);
	laststate = 0;
	scale.reset(new bool(false));

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CW);

	// Enable blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);

	glClearColor(39.0f / 255.0f, 58.0f / 255.0f, 93.0f / 255.0f, 1.0f);

	// UI part
	menu.reset(new Ragna::Menu);
	panel.reset(new Ragna::Panel);

	/*Header part of the panel */
	char* base_path = SDL_GetBasePath();

	if (base_path == nullptr) {
		base_path = SDL_strdup("./");
	}

	std::stringstream str_back;
	str_back << base_path << "Data/arrow_back.png";

	std::stringstream str_forw;
	str_forw << base_path << "Data/arrow_forward.png";

	std::stringstream str_menu;
	str_menu << base_path << "Data/menu.png";


	SDL_free(base_path);

	header_view.reset(new Ragna::View(false));
	header.reset(new Ragna::CardLayout(1, 4));
	shader.reset(new Ragna::BasicShader());
	header_rect.reset(new Ragna::Rect(500.0f, 500.0f, 9000.0f, 960.0f));

	header_rect->setColor(glm::vec4(0.0f, 0.4f, 0.7f, 1.0f));
	header_rect->setShader(shader);

	header_view->setLayout(header);
	header_view->setMaterialFace(header_rect);

	left_img.reset(new Ragna::Image);
	left_img->setImage(str_back.str());
	left_img->move(500.0f, 500.0f);
	std::shared_ptr<Ragna::Event> event_value(new BackEvent);
	left_img->setEvent(event_value);

	header->addItem(0, 0, left_img);

	header_text.reset(new Ragna::Text);
	header_text->setText("Text");
	header_text->setScale(0.2f);
	header_text->show();
	float width = header_text->getWidth();
	header_text->move(3000.0f - (width / 2), 500.0f);
	header->addItem(0, 1, header_text);

	menu_img.reset(new Ragna::Image);
	menu_img->setImage(str_menu.str());
	menu_img->move(7580.0f, 600.0f);
	header->addItem(0, 2, menu_img);

	std::shared_ptr<Ragna::Event> menu_event(new MenuEvent(menu));
	menu_img->setEvent(menu_event);

	right_img.reset(new Ragna::Image);
	right_img->setImage(str_forw.str());
	right_img->move(8540.0f, 500.0f);
	header->addItem(0, 3, right_img);

	std::shared_ptr<Ragna::Event> event_forw(new ForwEvent);
	right_img->setEvent(event_forw);

	panel->setPanelBar(header_view);

	/* Central part of the panel */
	central_view.reset(new Ragna::View(false));
	central.reset(new Ragna::CardLayout(2, 3));
	shader_central.reset(new Ragna::BasicShader);
	rect_face.reset(new Ragna::Rect(600.0f, 1440.0f, 8800.0f, 7900.0f));

	rect_face->setColor(glm::vec4(0.2f, 0.5f, 0.2f, 1.0f));
	rect_face->setShader(shader_central);
	rect_face->setZOrder(0.1f);

	// first scene
	first_scene.reset(new Ragna::Text);
	first_scene->setText("S");
	first_scene->setScale(4.0f);
	float width_first = first_scene->getWidth();
	float height_first = first_scene->getHeight();
	first_scene->move(5500.0f - (width_first / 2), 7600.0f - (height_first / 2));

	// second_scene
	second_scene.reset(new Ragna::Text);
	second_scene->hide();
	second_scene->setText("#Hello World!");
	second_scene->setScale(0.5f);
	float width_word = second_scene->getWidth();
	float height = second_scene->getHeight();
	second_scene->move(5000.0f - (width_word / 2), 5000.0f - (height / 2));

	// third_scene
	third_scene.reset(new Ragna::Text);
	third_scene->hide();
	third_scene->setText(basic_text);
	third_scene->setScale(0.3f);
	// float third_scene_width = third_scene->getWidth();
	float third_scene_height = third_scene->getHeight();
	third_scene->move(1000.0f, 5000.0f - (third_scene_height / 2));
	// third_scene->resize(9000.0f, third_scene_height);


	third_scene_shader.reset(new Ragna::BasicShader());
	third_scene_face.reset(new Ragna::Rect(1000.0f, 4500.0f, 8000.0f, third_scene_height * 2));
	third_scene_face->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	third_scene_face->setShader(third_scene_shader);
	third_scene_face->setZOrder(1.0f);
	third_scene->setMaterialFace(third_scene_face);


	//menu
	menu_view.reset(new Ragna::View(false));
	menu_layout.reset(new Ragna::CardLayout(2, 1));
	shader_menu.reset(new Ragna::BasicShader);
	menu_face.reset(new Ragna::Rect(7480.0f, 1400.0f, 2100.0f, 1800.0f));
	menu_face->setColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
	menu_face->setShader(shader_menu);
	menu_face->setZOrder(10.0f);

	// scale
	text_scale.reset(new Ragna::Text);
	text_scale->setText("Scale");
	text_scale->setScale(0.2f);
//	float width_scale = text_scale->getWidth();
	float height_scale = text_scale->getHeight();
	text_scale->move(7580.0f, 1600.0f - (height_scale / 2));

	std::shared_ptr<Ragna::Event> scale_event(new ScaleEvent(scale));
	text_scale->setEvent(scale_event);

	scale_shader.reset(new Ragna::BasicShader());
	scale_face.reset(new Ragna::Rect(7580.0f, 1500.0f, 1900.0f, height_scale));
	scale_face->setColor(glm::vec4(0.6f, 0.6f, 0.6f, 1.0f));
	scale_face->setShader(scale_shader);
	scale_face->setZOrder(11.0f);
	text_scale->setMaterialFace(scale_face);

	// bezier
	text_bezier.reset(new Ragna::Text);
	text_bezier->setText("Bezier");
	text_bezier->setScale(0.2f);
//	float width_bezier = text_bezier->getWidth();
	float height_bezier = text_bezier->getHeight();
	text_bezier->move(7580.0f, 1600.0f + 100.0f + height_scale - (height_bezier / 2));

	std::shared_ptr<Ragna::Event> bezier_event(new BezierEvent());
	text_bezier->setEvent(bezier_event);

	bezier_shader.reset(new Ragna::BasicShader());
	bezier_face.reset(new Ragna::Rect(7580.0f, 1500.0f + 100.0f + height_scale,
		1900.0f, height_bezier));
	bezier_face->setColor(glm::vec4(0.6f, 0.6f, 0.6f, 1.0f));
	bezier_face->setShader(bezier_shader);
	bezier_face->setZOrder(11.0f);
	text_bezier->setMaterialFace(bezier_face);

	menu_layout->addItem(0, 0, text_scale);
	menu_layout->addItem(0, 1, text_bezier);

	menu_view->setMaterialFace(menu_face);
	menu_view->setLayout(menu_layout);
	menu->setCentralView(menu_view);

	central->addItem(0, 0, first_scene);
	central->addItem(0, 1, second_scene);
	central->addItem(0, 2, third_scene);

	central_view->setMaterialFace(rect_face);
	central_view->setLayout(central);

	panel->setCentralView(central_view);

	menu->hide();
	panel->show();

	return true;
}


void App::cleanUp()
{
	window.destroy();
}


void App::update()
{
	int state = Ragna::Molten::getInstance().getState();

	if (laststate != state) {
		if (state == 1) {
			header_text->setText("Glyph rendering");

			first_scene->show();
			second_scene->hide();
			third_scene->hide();

			curr_scale = -4.0;

			SDL_StartTextInput();
		} else if (state == 2) {
			header_text->setText("Text rendering");

			first_scene->hide();
			second_scene->show();
			third_scene->hide();

			curr_scale = -0.5;
		} else if (state == 3) {
			header_text->setText("Edit text");
			first_scene->hide();
			second_scene->hide();
			third_scene->show();

			SDL_StartTextInput();
		}

		if (laststate == 3 ) {
			SDL_StopTextInput();
		}

		if (laststate == 1) {
			SDL_StopTextInput();
		}

		laststate = state;
	}

	float width = header_text->getWidth();
	header_text->move(5000.0f - (width / 2), 500.0f);

		if (state == 1) {
			if (*scale) {
				curr_scale += ((SDL_GetTicks() - lastTic)) * 0.0000001f;

				if (curr_scale > 4.0f) {
					curr_scale = -4.0f;
					lastTic = SDL_GetTicks();
				}

				first_scene->setScale(std::abs(curr_scale));
			}

		} else if (state == 2) {
			if (*scale) {
				curr_scale += ((SDL_GetTicks() - lastTic)) * 0.0000001f;

				if (curr_scale > 0.5f) {
					curr_scale = -0.5f;
					lastTic = SDL_GetTicks();
				}

				second_scene->setScale(std::abs(curr_scale));
			}
		}
}


void App::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Ragna::Molten::getInstance().renderScene();
	window.swapContext();
}


void App::handleInput()
{
	SDL_Event ev;
	while (SDL_PollEvent(&ev)) {
		switch (ev.type) {
			case SDL_QUIT :
				quit = true;
				break;

			case SDL_KEYDOWN:
				keyDownEvent(ev.key);

				switch (ev.key.keysym.sym) {
					case SDLK_BACKSPACE:
					{
						if (laststate == 3) {
							std::string event_text = third_scene->getText();

							if (event_text == basic_text) {
								break;
							}


							if (event_text.length() > 0) {
								event_text.pop_back();
							}

							if (event_text.empty()) {
								event_text = basic_text;
							}

							third_scene->setText(event_text);
						}
					}
					break;

					default:
					break;
				}
				break;

			case SDL_MOUSEBUTTONDOWN:
				mouseButtonDownEvent(ev.button);
				break;

			case SDL_MOUSEMOTION:
				mouseMotionEvent(ev.motion);
				break;

			case SDL_MOUSEWHEEL:
				mouseWheelEvent(ev.wheel);
				break;

			case SDL_WINDOWEVENT:
				windowEvent(ev.window);
				break;

			case SDL_TEXTINPUT:
			{
				if (laststate == 3) {
					std::string event_text = third_scene->getText();

					if (event_text.length() > 16) {
						break;
					}

					if (event_text == basic_text) {
						event_text.clear();
					}

					event_text += ev.text.text;
					third_scene->setText(event_text);
				}

				if (laststate == 1) {
					std::string event_text(ev.text.text);
					first_scene->setText(event_text);
				}
			}
			break;

			default:
				break;
		}
	}
}


void App::keyDownEvent(const SDL_KeyboardEvent& key)
{
	switch (key.keysym.sym) {
		case SDLK_ESCAPE:
			quit = true;
			break;
		default:
			break;
	}
}


void App::mouseButtonDownEvent(const SDL_MouseButtonEvent& button)
{
	Ragna::Molten::getInstance().mouseButtonDown(button);
}


void App::mouseMotionEvent(const SDL_MouseMotionEvent& /*motion*/)
{
}


void App::windowEvent(const SDL_WindowEvent& window)
{
	if (window.event == SDL_WINDOWEVENT_RESIZED) {
		glViewport(0, 0, window.data1, window.data2);

		Ragna::Molten::getInstance().setResolution(window.data1, window.data2);
	}
}


void App::mouseWheelEvent(const SDL_MouseWheelEvent& wheel)
{
	int cont = std::abs(wheel.y);
	for (int i = 0; i < cont; i++) {
		if (wheel.y < 0) {
			Ragna::Molten::getInstance().decreaseScale();
		} else {
			Ragna::Molten::getInstance().increaseScale();
		}
	}
}
