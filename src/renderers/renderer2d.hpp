#pragma once


#include <iostream>
#include <SDL3/SDL.h>

namespace gep::renderers
{

	class [[nodiscard]] renderer2d
	{
	public:
		static auto instance() -> renderer2d& {
			static renderer2d static_instance;
			return static_instance;
		}

		renderer2d(const renderer2d&) = delete;
		renderer2d(renderer2d&&) = delete;
		renderer2d operator=(const renderer2d&) = delete;
		renderer2d operator=(const renderer2d&&) = delete;

		auto Load() noexcept -> bool;
		auto Begin() noexcept -> void;
		auto DrawQuad() noexcept -> void;
		auto End(SDL_Window* window) noexcept -> void;
		auto Delete() noexcept -> void;

	private:
		renderer2d() = default;
		~renderer2d() = default;

		uint32_t vao = 0;
		uint32_t vbo = 0;
		uint32_t ebo = 0;

	};
}