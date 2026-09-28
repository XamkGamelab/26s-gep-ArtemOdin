#pragma once
union SDL_Event;

#include <iostream>
#include <unordered_set>
#include <SDL3/SDL_events.h>

using namespace std;

namespace gep::input
{

	class [[nodiscard]] input_system
	{
	public:
		static auto instance() -> input_system& {
			static input_system static_instance;
			return static_instance;
		}

		input_system(const input_system&) = delete;
		input_system(input_system&&) = delete;
		input_system operator=(const input_system&) = delete;
		input_system operator=(const input_system&&) = delete;

		auto ProcessEvent(const SDL_Event&) noexcept -> void;
		auto Update() noexcept -> void;
		auto IsKeyDown(SDL_Keycode key) const noexcept -> bool;
		auto IsKeyUp(SDL_Keycode key) const noexcept -> bool;
		auto IsKeyPressed(SDL_Keycode key) const noexcept -> bool;
		auto IsMouseDown(unsigned int mouseBtnIdx) const noexcept -> bool;
		auto IsMouseUp(unsigned int mouseBtnIdx) const noexcept -> bool;
		auto IsMousePressed(unsigned int mouseBtnIdx) const noexcept -> bool;

	private:
		input_system() = default;
		~input_system() = default;

		auto Clear() noexcept -> void;

		unordered_set<SDL_Keycode> pressedDown;
		unordered_set<SDL_Keycode> pressedUp;
		unordered_set<SDL_Keycode> pressedNow;
		unordered_set<unsigned int> mousePressedDown;
		unordered_set<unsigned int> mousePressedUp;
		unordered_set<unsigned int> mousePressedNow;

	};
}