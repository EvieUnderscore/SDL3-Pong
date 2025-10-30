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

			SDL_FRect arenaTop;
			SDL_FRect arenaTopL;
			SDL_FRect arenaTopR;
			SDL_FRect arenaBottom;
			SDL_FRect arenaBottomL;
			SDL_FRect arenaBottomR;

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
			SDL_RenderClear(renderer);

			SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

			float arenaHeightOffset = 20;
			arenaTop.w = arenaBottom.w = WINDOW_WIDTH / 1.25;
			arenaTop.h = arenaBottom.h = 10;
			arenaTop.x = arenaBottom.x = (WINDOW_WIDTH / 2) - (arenaTop.w / 2);
			arenaTop.y = arenaHeightOffset;
			arenaBottom.y = (WINDOW_HEIGHT - arenaBottom.h) - arenaHeightOffset;
			
			arenaTopL.w = arenaBottomL.w = arenaBottomR.w = arenaTopR.w = 10;
			arenaTopL.h = arenaBottomL.h = arenaBottomR.h = arenaTopR.h = WINDOW_HEIGHT / 4;
			arenaTopL.x = arenaBottomL.x = arenaTop.x;
			arenaTopL.y = arenaTopR.y = arenaTop.y;

			arenaTopR.x = arenaBottomR.x = arenaTop.x + (arenaTop.w);
			arenaBottomL.y = arenaBottomR.y = (WINDOW_HEIGHT - arenaBottomL.h) - arenaHeightOffset;

			SDL_RenderFillRect(renderer, &arenaTop);
			SDL_RenderFillRect(renderer, &arenaTopL);
			SDL_RenderFillRect(renderer, &arenaTopR);
			SDL_RenderFillRect(renderer, &arenaBottom);
			SDL_RenderFillRect(renderer, &arenaBottomL);
			SDL_RenderFillRect(renderer, &arenaBottomR);

			for (int y = int(arenaHeightOffset); y < WINDOW_HEIGHT - arenaHeightOffset; y += 20 + (arenaBottom.y - arenaTop.y) * 0.01) {
				SDL_FRect dashRect = {(WINDOW_WIDTH / 2) - (5 / 2),y,5,20};
				if (dashRect.y > (WINDOW_HEIGHT - arenaHeightOffset) - dashRect.h) { dashRect.y = (WINDOW_HEIGHT - arenaHeightOffset) + (dashRect.y - dashRect.h); }
				SDL_RenderFillRect(renderer, &dashRect);
			}

			SDL_RenderPresent(renderer);

		}

		
	}

	// uninit everything here

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}