#include <iostream>
#include <FrameWindow.hpp>

int main(int /*argc*/, char** /*argv*/)
{
	FrameWindow window("SDLTest");

	window.create();
	SDL_Rect rect = {100, 100, 400, 600};
	window.setDimension(rect);

	SDL_Event ev;
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&ev)) {
			switch (ev.type) {
				case SDL_QUIT :
					quit = true;
					break;

				case SDL_KEYDOWN:
					switch (ev.key.keysym.sym) {
						case SDLK_ESCAPE:
							quit = true;
							break;

						default:
							break;
					}
					break;

				default:
					break;
			}
		}
	}

	window.destroy();

	return 0;
}
