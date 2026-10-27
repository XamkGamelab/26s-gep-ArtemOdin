#include "renderer_2d.hpp"
#include "texture_2d.hpp"
#include <glad/gl.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_pixels.h>

namespace gep::renderer
{
	renderer_2d::renderer_2d()
	{
		shader_program = shader{ "assets/shaders/vertex.glsl", "assets/shaders/frag.glsl" };
		init_quad();
	}

	renderer_2d::~renderer_2d()
	{
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ebo);
		shader_program.clear();
	}

	auto renderer_2d::clear() const noexcept -> void
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	auto renderer_2d::draw_quad(const texture_2d& texture) const -> void
	{
		shader_program.bind();
		glBindVertexArray(vao);
		texture.bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	auto renderer_2d::init_quad() -> void
	{

		float vertices[] = {
			// X     Y     U     V
			 0.5f,  0.5f, 1.0f, 1.0f, // top right
			 0.5f, -0.5f, 1.0f, 0.0f,// bottom right
			-0.5f, -0.5f, 0.0f, 0.0f, // bottom left
			-0.5f,  0.5f, 0.0f, 1.0f // top left 
		};

		uint32_t indices[] = {  // note that we start from 0!
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		uint32_t element_component_count = 2; // Vertex --> from 2 components
		uint32_t element_size = 4 * sizeof(float);
		uint32_t vertex_count = sizeof(vertices) / element_size;
		glVertexAttribPointer(0,
			element_component_count, GL_FLOAT, GL_FALSE, element_size, (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1,
			element_component_count, GL_FLOAT, GL_FALSE, element_size, (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);

	}
}