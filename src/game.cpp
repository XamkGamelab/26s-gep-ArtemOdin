#include "game.hpp"
#include <iostream>
#include <algorithm>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_rect.h>
#include <SDL3_image/SDL_image.h>
#include "input/input_system.hpp"

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


	if (window == nullptr) {
		SDL_LogError(SDL_LOG_CATEGORY_VIDEO, 
			"SDL WINDOW CREATION FAILED %s", SDL_GetError());
		return false;
	}

	if (renderer == nullptr) {
		SDL_LogError(SDL_LOG_CATEGORY_RENDER,
			"SDL RENDERER CREATION FAILED %s", SDL_GetError());
		return false;
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	image = IMG_LoadTexture(renderer, "assets/awesomeface.png");

	if (!image)
	{
		SDL_Log("IMAGE LOAD ERROR: %s", SDL_GetError());
	}
	
	return true;


}

auto gep::game::run() -> void
{
	//SDL_GetWindowSurface(window);
	//SDL_UpdateWindowSurface(window);



	bool IsRunning = true;

	int32_t width;
	int32_t height;

	SDL_GetWindowSize(window, &width, &height);

	float imageX;
	float imageY;

	imageX = width / 2;
	imageY = height / 2;

	imageX -= image->w / 2;
	imageY -= image->h / 2;

	while (IsRunning) {


		SDL_Event Event;

		auto& input_system = input::input_system::instance();

		input_system.Update();

		while (SDL_PollEvent(&Event))
		{

			if (Event.type == SDL_EVENT_QUIT)
			{
				IsRunning = false;
				return;
			}

			
			if (Event.type == SDL_EVENT_KEY_DOWN ||
				Event.type == SDL_EVENT_KEY_UP ||
				Event.type == SDL_EVENT_MOUSE_BUTTON_DOWN ||
				Event.type == SDL_EVENT_MOUSE_BUTTON_UP)
			{
	
				input_system.ProcessEvent(Event);

				if (input_system.IsKeyDown(SDLK_ESCAPE))
				{
					IsRunning = false;
					break;
				}
			}


			if (Event.type == SDL_EVENT_WINDOW_RESIZED)
			{
				

				SDL_GetWindowSize(window, &width, &height);

				width = std::clamp(width, 512, 1920);

				height = std::clamp(height, 512, 1080);

				SDL_SetWindowSize(window, width, height);

				imageX = width / 2;
				imageY = height / 2;

				imageX -= image->w / 2;
				imageY -= image->h / 2;

				SDL_Log("Window resized to %d x %d", width, height);

			}			

			

		}
		

		SDL_RenderClear(renderer);

		if (image)
		{
			if (input_system.IsKeyPressed(SDLK_W))
				imageY -= 3;
			if (input_system.IsKeyPressed(SDLK_A))
				imageX -= 3;
			if (input_system.IsKeyPressed(SDLK_S))
				imageY += 3;
			if (input_system.IsKeyPressed(SDLK_D))
				imageX += 3;


			imageX = std::clamp(imageX, 0.0f, static_cast<float>(width - image->w));

			imageY = std::clamp(imageY, 0.0f, static_cast<float>(height - image->h));

			SDL_FRect destinationRect;
			destinationRect.h = image->h;
			destinationRect.w = image->w;
			destinationRect.x = imageX;
			destinationRect.y = imageY;

			SDL_RenderTexture(renderer, image, 0, &destinationRect);
		}

		SDL_RenderPresent(renderer);
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


