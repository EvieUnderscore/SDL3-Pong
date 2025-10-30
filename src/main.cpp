#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_main.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 960

int main(int argc, char* argv[])
{
	// init everything here

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_FRect rect;

	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldnt Init SDL: %s", SDL_GetError());
		return 3;
	}

	if (!SDL_CreateWindowAndRenderer("20 Games Challenge | Pong", WINDOW_WIDTH, WINDOW_HEIGHT, NULL, &window, &renderer)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldnt create window: %s", SDL_GetError());
		return 3;
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

			SDL_FRect rect;
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
			SDL_RenderClear(renderer);

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);  /* blue, full alpha */
			rect.w = rect.h = 100;
			rect.x = (WINDOW_WIDTH / 2) - (rect.w / 2);
			rect.y = (WINDOW_HEIGHT / 2) - (rect.h / 2);

			SDL_RenderFillRect(renderer, &rect);


			SDL_RenderPresent(renderer);

		}

		
	}

	// uninit everything here

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}