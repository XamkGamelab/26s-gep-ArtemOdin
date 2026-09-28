#include "time_system.hpp"
#include <SDL3/SDL_events.h>

#include <chrono>
#include <iostream>
#include <algorithm>

auto gep::time::time_system::Init() noexcept -> void
{
	lastTime = std::chrono::steady_clock::now();
	deltaTime = 0;
}

auto gep::time::time_system::Tick() noexcept -> void
{
	nowTime = std::chrono::steady_clock::now();
	deltaTime = std::min(std::chrono::duration<float>(nowTime- lastTime).count(), 0.0333f);
	lastTime = nowTime;
}

auto gep::time::time_system::GetDeltaTime() const noexcept -> float
{

	return deltaTime;
}


