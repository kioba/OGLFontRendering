#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <RunicFont.hpp>
#include <RunicGlyph.hpp>
#include <SDL_image.h>
#include <sstream>
#include <thread>
#include <vector>

#ifdef WIN32
	#include <SDL.h>
#else
	#include <SDL2/SDL.h>
#endif

bool Intersect(SDL_Rect& clicked, std::vector<SDL_Rect>& points);
void paintCubicBazier(SDL_Renderer* context, std::vector<SDL_Rect>& points);
void paintQuadBazier(SDL_Renderer* context, std::vector<SDL_Rect>& points);
void paintGlyph(SDL_Renderer* context, const Runic::Glyph glyph, const int height, int& num_tri);


int main(int /*argc*/, char** /*argv*/)
{
	// Start SDL
	if (SDL_Init (SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	int width = 1140;
	int height = 540;

	SDL_Window* window = SDL_CreateWindow ("Runic Font Tester",
										SDL_WINDOWPOS_UNDEFINED,
										SDL_WINDOWPOS_UNDEFINED,
										width, height,
										 SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

	if (window == nullptr) {
		std::cout << "SDL_Window could not be initialized!" << std::endl;
		return -1;
	}

	SDL_Renderer* context = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (context == nullptr) {
		std::cout << "SDL_Renderer could not be initialized!" << std::endl;
		return -1;
	}

	char* base_path = SDL_GetBasePath();

	if (base_path == nullptr) {
		base_path = SDL_strdup("./");
	}

	std::stringstream str_buff;
	str_buff << base_path << "Data/Roboto-Black.ttf";

	std::stringstream str_buff_img;
	str_buff_img << base_path << "Data/frame.png";

	SDL_Surface* image = IMG_Load(str_buff_img.str().c_str());
	if (image == nullptr) {
		printf("Error: \"%s\"\n",SDL_GetError());
		return -1;
	}

	std::stringstream str_buff_back;
	str_buff_back << base_path << "Data/grungeframe.png";

	SDL_Surface* back_image = IMG_Load(str_buff_back.str().c_str());
	if (back_image == nullptr) {
		printf("Error: \"%s\"\n",SDL_GetError());
		return -1;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(context, image);
	SDL_Texture* back_texture = SDL_CreateTextureFromSurface(context, back_image);

	if (image != nullptr) {
		SDL_FreeSurface(image);
	}

	if (back_image != nullptr) {
		SDL_FreeSurface(back_image);
	}

	SDL_free(base_path);

	Runic::RFont font(str_buff.str());
	Runic::Glyph glyph = font.getGlyph('S');
	bool quit = false;
	bool paint = true;
	int num_tri = -1;

	SDL_StartTextInput();
	while (!quit) {
		SDL_Event ev;

		while (SDL_PollEvent (&ev)) {
			switch (ev.type) {
				case SDL_QUIT:
					quit = true;
					break;

				case SDL_WINDOWEVENT:
					switch (ev.window.event) {
						case SDL_WINDOWEVENT_SHOWN:
						case SDL_WINDOWEVENT_HIDDEN:
						case SDL_WINDOWEVENT_EXPOSED:
						case SDL_WINDOWEVENT_MOVED:
						case SDL_WINDOWEVENT_MINIMIZED:
						case SDL_WINDOWEVENT_MAXIMIZED:
						case SDL_WINDOWEVENT_RESTORED:
						case SDL_WINDOWEVENT_RESIZED:
							paint = true;
							break;

						case SDL_WINDOWEVENT_SIZE_CHANGED:
							//width = ev.window.data1;
							// std::cout << width << std::endl;
							//height = ev.window.data2;
							// std::cout << height << std::endl;
							paint = true;
							break;
					}
					break;

				case SDL_TEXTINPUT:
				{
					/* Add new text onto the end of our text */
					std::string event_text(ev.text.text);
					glyph = font.getGlyph(event_text.back());
					paint = true;
					num_tri = -1;
				}
					break;
				case SDL_KEYDOWN:
				{
					switch (ev.key.keysym.sym) {
						case SDLK_F2:
							if (num_tri == -1) {
								num_tri = -2;
							} else {
								num_tri = -1;
							}
							paint = true;
						break;

						case SDLK_F3:
							if (num_tri == -2 || num_tri == -1) {
								num_tri = 1;
							} else if (num_tri > 0) {
								num_tri += 1;
							}

							paint = true;
						break;

						case SDLK_F5:
							paint = true;
							break;
					}
				}
				break;

				case SDL_MOUSEBUTTONDOWN:
					{
						if (ev.button.button == SDL_BUTTON_LEFT) {
							paint = true;
						}

						if (ev.button.button == SDL_BUTTON_RIGHT) {
							paint = true;
						}
					}
					break;

				default:
					break;
			}
		}


		if (paint) {
			paint = false;
			SDL_SetRenderDrawColor(context, 59, 78, 113, 0xFF);
			SDL_RenderClear(context);

			SDL_RenderCopy(context, back_texture, nullptr, nullptr);

			paintGlyph(context, glyph, height, num_tri);

			SDL_Rect rect;
			rect.x = 50;
			rect.y = 100;
			rect.w = 500;
			rect.h = 300;
			SDL_RenderCopy(context, texture, nullptr, &rect);

			SDL_RenderPresent(context);
		}
	}

	SDL_StopTextInput();

	if (context != nullptr) {
		SDL_DestroyRenderer (context);
		context = nullptr;
	}

	if (window != nullptr) {
		SDL_DestroyWindow (window);
		window = nullptr;
	}

	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
	}

	if (back_texture != nullptr) {
		SDL_DestroyTexture(back_texture);
	}

	// Quit SDL
	SDL_Quit();
	return 0;
}

void paintGlyph(SDL_Renderer* context, const Runic::Glyph glyph, const int height, int& num_tri)
{
	SDL_SetRenderDrawColor(context, 0, 0, 0, 100);
	for (unsigned int i = 0; i < glyph.triangles.size(); ++i) {
		SDL_Point first_rect;
		first_rect.x = (int) glyph.triangles[i].a.first;
		first_rect.y = (int) glyph.triangles[i].a.second;

		first_rect.x = (first_rect.x + 3500) / 5;
		first_rect.y = height - (first_rect.y + 1000) / 5;

		SDL_Point second_rect;
		second_rect.x = (int) glyph.triangles[i].b.first;
		second_rect.y = (int) glyph.triangles[i].b.second;

		second_rect.x = (second_rect.x + 3500) / 5;
		second_rect.y = height - (second_rect.y + 1000) / 5;

		SDL_Point third_rect;
		third_rect.x = (int) glyph.triangles[i].c.first;
		third_rect.y = (int) glyph.triangles[i].c.second;

		third_rect.x = (third_rect.x + 3500) / 5;
		third_rect.y = height - (third_rect.y + 1000) / 5;
		SDL_RenderDrawLine(context, first_rect.x, first_rect.y,
									second_rect.x, second_rect.y);

		SDL_RenderDrawLine(context, second_rect.x, second_rect.y,
									third_rect.x, third_rect.y);

		SDL_RenderDrawLine(context, first_rect.x, first_rect.y,
									third_rect.x, third_rect.y);
	}

	int num_triangles = glyph.bezier.size();

	if (num_tri == -2) {
		num_triangles = 0;
	} else if (num_tri == -1) {
		num_triangles = glyph.bezier.size();
	} else if (num_tri >= 0) {
		num_triangles = std::min(num_tri, num_triangles);
	}

	if (num_tri != -1 && num_triangles == (signed)(glyph.bezier.size())) {
		num_tri = -1;
	}

	for (int i = 0; i < num_triangles; ++i) {
		SDL_Rect rect_a;
		rect_a.x = (int) glyph.bezier[i].a.first - 2;
		rect_a.y = (int) glyph.bezier[i].a.second - 2;
		rect_a.w = 2;
		rect_a.h = 2;

		rect_a.x = (rect_a.x + 3500) / 5;
		rect_a.y = height - (rect_a.y + 1000) / 5;

		SDL_Rect rect_b;
		rect_b.x = (int) glyph.bezier[i].b.first - 2;
		rect_b.y = (int) glyph.bezier[i].b.second - 2;
		rect_b.w = 2;
		rect_b.h = 2;


		rect_b.x = (rect_b.x + 3500) / 5;
		rect_b.y = height - (rect_b.y + 1000) / 5;

		SDL_Rect rect_c;
		rect_c.x = (int) glyph.bezier[i].c.first - 2;
		rect_c.y = (int) glyph.bezier[i].c.second - 2;
		rect_c.w = 2;
		rect_c.h = 2;

		rect_c.x = (rect_c.x + 3500) / 5;
		rect_c.y = height - (rect_c.y + 1000) / 5;

		std::vector<SDL_Rect> bezier_points;
		bezier_points.push_back(rect_a);
		bezier_points.push_back(rect_b);
		bezier_points.push_back(rect_c);
		paintQuadBazier(context, bezier_points);
	}
}


bool Intersect(SDL_Rect& clicked, std::vector<SDL_Rect>& points)
{
	for (unsigned int i = 0; i < points.size(); ++i) {
		if (SDL_HasIntersection(&clicked, &points[i])) {
			return true;
		}
	}
	return false;
}


int getPt(int n1 , int n2 , float perc)
{
	int diff = n2 - n1;

	return static_cast<int>(n1 + ( diff * perc ));
}


void paintCubicBazier(SDL_Renderer* context, std::vector<SDL_Rect>& points)
{
	std::vector<SDL_Point> vec;
	SDL_SetRenderDrawColor(context, 255, 150, 0, 50);

	for(float i = 0; i <= 1; i += 0.01f) {
		SDL_Point spot;
		spot.x = static_cast<int>(pow(1.0f - i, 3.0f) * points[0].x + 3  * i * pow(1.0f - i, 2.0f) * points[1].x + 3 * pow(i, 2.0f) * (1.0f - i) * points[2].x + pow(i, 3.0f) * points[3].x);
		spot.y = static_cast<int>(pow(1.0f - i, 3.0f) * points[0].y + 3  * i * pow(1.0f - i, 2.0f) * points[1].y + 3 * pow(i, 2.0f) * (1.0f - i) * points[2].y + pow(i, 3.0f) * points[3].y);
		vec.push_back(spot);
	}

	SDL_RenderDrawLines (context, &vec[0], vec.size());
}


void paintQuadBazier(SDL_Renderer* context, std::vector<SDL_Rect>& points)
{
	// draw control point
	SDL_SetRenderDrawColor(context, 255, 0, 255, 50);
	SDL_Rect rect;
	rect.x = points[1].x - 2;
	rect.y = points[1].y - 2;
	rect.w = 4;
	rect.h = 4;

	SDL_RenderFillRect(context, &rect);

	// draw points on the curve
	std::vector<SDL_Point> vec;
	SDL_SetRenderDrawColor(context, 255, 0, 0, 50);

	for(float i = 0; i <= 1; i += 0.01f) {
		// The Green Line
		int xa = getPt(points[0].x, points[1].x, i);
		int ya = getPt(points[0].y, points[1].y, i);
		int xb = getPt(points[1].x, points[2].x, i);
		int yb = getPt(points[1].y, points[2].y, i);

		// The Black Dot
		SDL_Point spot;
		spot.x = getPt(xa, xb, i);
		spot.y = getPt(ya, yb, i);

		vec.push_back(spot);
	}

	SDL_RenderDrawLines (context, &vec[0], vec.size());
}
