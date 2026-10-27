#pragma once
#include "shader.hpp"
#include "texture_2d.hpp"

namespace gep::renderer
{
	class [[nodiscard]] renderer_2d
	{
	public:
		renderer_2d();
		~renderer_2d();

		auto clear() const noexcept -> void;
		auto draw_quad(const texture_2d& texture) const -> void;

		renderer_2d(const renderer_2d&) = delete;
		renderer_2d(renderer_2d&&) = delete;
		renderer_2d operator=(const renderer_2d&) = delete;
		renderer_2d operator=(renderer_2d&&) = delete;

	private:
		uint32_t vao{ 0 }, vbo{ 0 }, ebo{ 0 };
		shader shader_program;
		auto init_quad() -> void;
	};
}