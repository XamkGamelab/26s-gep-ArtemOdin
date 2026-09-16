#include "game.hpp"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>


auto gep::game::init() noexcept -> bool 
{

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, 
			"SDL INIT FAILED %s", SDL_GetError());
		return false;
	}

	SDL_CreateWindowAndRenderer(
		"GAME",                 
		1280,                           
		720,        
		SDL_WINDOW_RESIZABLE,
		&window,
		&renderer
	);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	if (window == nullptr) {
		SDL_LogError(SDL_LOG_CATEGORY_VIDEO, 
			"SDL WINDOW CREATION FAILED %s", SDL_GetError());
		return false;
	}

	return true;


}

auto gep::game::run() -> void
{
	//SDL_GetWindowSurface(window);
	//SDL_UpdateWindowSurface(window);



	bool IsRunning = true;
	while (IsRunning) {


		SDL_Event Event;



		while (SDL_PollEvent(&Event))
		{


			switch (Event.type)
			{
			case SDL_EVENT_KEY_DOWN:
			{
				switch (Event.key.scancode)
				{
				case SDL_SCANCODE_W:
					SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
					break;

				case SDL_SCANCODE_A:
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
					break;

				case SDL_SCANCODE_S:
					SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
					break;

				case SDL_SCANCODE_D:
					SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
					break;

				case SDL_SCANCODE_ESCAPE:
					IsRunning = false;
					break;


				}
				break;
				
			}
			case SDL_EVENT_WINDOW_RESIZED:

				int width;
				int height;

				SDL_GetWindowSize(window, &width, &height);

				SDL_Log("Tried to resize to %d x %d", width, height);

				SDL_SetWindowSize(window, 1280, 720);

				break;
			case SDL_EVENT_QUIT:
				IsRunning = false;
				break;
			}
		
		
			SDL_RenderClear(renderer);
			SDL_RenderPresent(renderer);
			
		}

	

	}

	shutdown();
}

auto gep::game::shutdown() noexcept -> void
{
	if (window != nullptr) {
		SDL_DestroyWindow(window);
	}
	if (renderer != nullptr) {
		SDL_DestroyRenderer(renderer);
	}
	SDL_Quit();
}


