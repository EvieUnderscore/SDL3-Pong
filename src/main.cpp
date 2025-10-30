#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_main.h>

int main(int argc, char* argv[])
{
	// init everything here

	SDL_Window* window;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS);
	window = SDL_CreateWindow(
		"20 Games Challenge | Pong", 
		1280, 960, 
		NULL
	);
	if (window == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	// main game loop

	bool running = true;
	while (running) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			// polled event behavior

			if (event.type == SDL_EVENT_QUIT) {
				running = false;
			}
		}

		
	}

	// uninit everything here

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}