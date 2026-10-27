#pragma once
#include <unordered_set>
#include <cstdint>

union SDL_Event;

namespace gep::input
{
	class [[nodiscard]] input_system
	{
	public:
		static auto instance() -> input_system&
		{
			static input_system static_instance;
			return static_instance;
		}

		input_system(const input_system&) = delete;
		input_system(input_system&&) = delete;
		input_system operator=(const input_system&) = delete;
		input_system operator=(input_system&&) = delete;

		auto update() noexcept -> void;
		auto process_input(const SDL_Event&) noexcept -> void;

		auto is_key_down(uint32_t) const noexcept -> bool;
		auto is_key_pressed(uint32_t) const noexcept -> bool;
		auto is_key_up(uint32_t) const noexcept -> bool;
		auto is_mouse_down(uint8_t) const noexcept -> bool;
		auto is_mouse_pressed(uint8_t) const noexcept -> bool;
		auto is_mouse_up(uint8_t) const noexcept -> bool;

	private:
		input_system() = default;
		~input_system() = default;

		std::unordered_set<uint32_t> keysDown{};
		std::unordered_set<uint32_t> keysPressed{};
		std::unordered_set<uint32_t> keysUp{};
		std::unordered_set<uint8_t> mouseDown{};
		std::unordered_set<uint8_t> mousePressed{};
		std::unordered_set<uint8_t> mouseUp{};
	};
}