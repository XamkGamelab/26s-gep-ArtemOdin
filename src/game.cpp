#include <glad/gl.h>
#include "game.hpp"

#include <string>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_mouse.h>

#include <SDL3_image/SDL_image.h>

#include "input/input_system.hpp"
#include "renderer/renderer_2d.hpp"
#include "renderer/texture_2d.hpp"


auto gep::game::init() noexcept -> bool
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"SDL_Init failed: %s", SDL_GetError());
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	window_handle = SDL_CreateWindow("Gep", 1280, 720, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	if (window_handle == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_VIDEO,
			"SDL_CreateWindow failed: %s", SDL_GetError());
		return false;
	}

	gl_context = SDL_GL_CreateContext(window_handle);
	auto version = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);
	if (version == 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_SYSTEM,
			"SDL_GL_CreateContext failed: %s", SDL_GetError());
		return false;
	}

	int32_t major, minor, profile;
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major);
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor);
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &profile);

	SDL_Log("OpenGL version: %i.%i - Profile: %i", major, minor, profile);
	SDL_Log("GLAD version: %i.%i", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

	glClearColor(58 / 255.f, 51 / 255.f, 51 / 255.f, 1.0f);

	return true;
}

auto gep::game::run() -> void
{
	int32_t window_width;
	int32_t window_height;
	SDL_GetWindowSize(window_handle, &window_width, &window_height);

	auto& input_system = input::input_system::instance();
	renderer::renderer_2d renderer{};

	auto speed = 5.0f;

	bool is_running = true;

	renderer::texture_2d texture1{"assets/textures/awesomeface.png"};

	while (is_running)
	{
		input_system.update();

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT)
			{
				is_running = false;
				return;
			}

			if (event.type == SDL_EVENT_WINDOW_RESIZED)
			{
				SDL_GetWindowSize(window_handle, &window_width, &window_height);
				SDL_Log("Window resized: %i %i", window_width, window_height);
			}

			input_system.process_input(event);
		}

		renderer.clear();
		renderer.draw_quad(texture1);
		SDL_GL_SwapWindow(window_handle);
	}
}

auto gep::game::shutdown() noexcept -> void
{
	if (gl_context != nullptr)
	{
		SDL_GL_DestroyContext(gl_context);
	}

	if (window_handle != nullptr)
	{
		SDL_DestroyWindow(window_handle);
	}

	SDL_Quit();
}