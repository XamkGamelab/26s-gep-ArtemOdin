#pragma once

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

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
		
		
		
	};
}

