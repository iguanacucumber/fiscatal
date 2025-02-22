#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

int main(void) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	SDL_CreateWindowAndRenderer("FiscAtal", 800, 600, 0, &window, &renderer);
	// SDL_SetWindowFullscreen(window, true);

	bool quit = false;
	while (!quit) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) quit = true;
		}

		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderPresent(renderer);
	}

	SDL_Quit();
	return 0;
}
