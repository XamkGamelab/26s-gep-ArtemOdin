#pragma once
#include <string_view>
#include <cstdint>

namespace gep::renderer
{
	class [[nodiscard]] texture_2d
	{
	public:
		texture_2d() = default;
		~texture_2d();
		texture_2d(const char* t_path);

		auto get_id() const noexcept -> uint32_t { return id; }
		auto bind() const noexcept -> void;
		auto clear() -> void;

		texture_2d(const texture_2d&) = delete;
		texture_2d& operator=(const texture_2d&) = delete;

		texture_2d(texture_2d&& rhs) noexcept;
		texture_2d& operator=(texture_2d&& rhs) noexcept;
		uint32_t width = 0;
		uint32_t height = 0;

	private:
		uint32_t id{ 0 };
	};
}