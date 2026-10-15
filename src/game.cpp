#include "game.hpp"
#include <iostream>
#include <algorithm>
#include <chrono>


#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_rect.h>
#include <SDL3_image/SDL_image.h>
#include <glad/gl.h>


#include "input/input_system.hpp"
#include "time/time_system.hpp"
#include "files/file_loader.hpp"
#include "shaders/shader.hpp"
#include "renderers/renderer2d.hpp"

auto gep::game::init() noexcept -> bool 
{

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, 
			"SDL INIT FAILED %s", SDL_GetError());
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	window = SDL_CreateWindow("OpenGL Window", 1280, 720, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (window == nullptr) {
		SDL_LogError(SDL_LOG_CATEGORY_VIDEO,
			"SDL WINDOW CREATION FAILED %s", SDL_GetError());
		return false;
	}

	context = SDL_GL_CreateContext(window);

	auto version = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);

	if (version == 0) {
		SDL_LogError(SDL_LOG_CATEGORY_SYSTEM,
			"OPENGL CONTEXT CREATION FAILED %s", SDL_GetError());
		return false;
	}


	int32_t major, minor, profile;
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major);
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor);
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &profile);

	SDL_Log("OpenGL version %i %i - Profile: %i ", major, minor, profile);
	SDL_Log("Glad version: %i %i", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));
	

	if (!shaders::shader::instance().Load("assets/shaders/vertex.glsl", 
		"assets/shaders/frag.glsl"))
	{
		shutdown();
		return false;
	}

	if (!renderers::renderer2d::instance().Load())
	{
		shutdown();
		return false;
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

	

	float moveSpeed = 120;
	float imageSize = 256;

	imageX -= imageSize / 2;
	imageY -= imageSize / 2;

	auto& input_system = input::input_system::instance();

	auto& shader = shaders::shader::instance();

	auto& renderer2d = renderers::renderer2d::instance();

	auto& time_system = time::time_system::instance();

	time_system.Init();


	while (IsRunning) 
	{

		SDL_Event Event;

		input_system.Update();
		time_system.Tick();

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

				imageX -= imageSize / 2;
				imageY -= imageSize / 2;

				SDL_Log("Window resized to %d x %d", width, height);

			}			

			

		}

		renderer2d.Begin();

		renderer2d.DrawQuad();

		renderer2d.End(window);

		//SDL_RenderPresent(renderer);
	}

	shutdown();
}

auto gep::game::shutdown() noexcept -> void
{
	shaders::shader::instance().Delete();
	renderers::renderer2d::instance().Delete();

	if (context != nullptr) {
		SDL_GL_DestroyContext(context);
	}

	if (window != nullptr) {
		SDL_DestroyWindow(window);
	}

	if (renderer != nullptr) {
		SDL_DestroyRenderer(renderer);
	}


	if (image != nullptr) {
		SDL_DestroyTexture(image);
	}

	SDL_Quit();
}

