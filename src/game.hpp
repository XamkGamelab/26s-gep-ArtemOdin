#pragma once

#include <SDL3/SDL.h>

namespace gep 
{

	class [[nodiscard]] game
	{
	public:
		

		[[nodiscard]] 
		auto init() noexcept -> bool;
		auto run() -> void;
		auto shutdown() noexcept -> void;

	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Texture* image;
		SDL_GLContext context;

		
		
	};
}

