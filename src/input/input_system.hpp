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

		auto ProcessEvent(const SDL_Event&) -> void;
		auto Update() -> void;
		auto IsKeyDown(SDL_Keycode key) -> bool;
		auto IsKeyUp(SDL_Keycode key) -> bool;
		auto IsKeyPressed(SDL_Keycode key) -> bool;
		auto IsMouseDown(unsigned int mouseBtnIdx) -> bool;
		auto IsMouseUp(unsigned int mouseBtnIdx) -> bool;
		auto IsMousePressed(unsigned int mouseBtnIdx) -> bool;

	private:
		input_system() = default;
		~input_system() = default;

		auto Clear() -> void;

		std::unordered_set<SDL_Keycode> pressedDown;
		std::unordered_set<SDL_Keycode> pressedUp;
		std::unordered_set<SDL_Keycode> pressedNow;
		std::unordered_set<unsigned int> mousePressedDown;
		std::unordered_set<unsigned int> mousePressedUp;
		std::unordered_set<unsigned int> mousePressedNow;

	};
}