#include "renderer2d.hpp"
#include <glad/gl.h>
#include "../shaders/shader.hpp"

auto gep::renderers::renderer2d::Load() noexcept -> bool
{

	//quad
	float vertices[]
	{
		// X      Y
		-0.5f, -0.5f, 
		 0.5f, -0.5f, 
		 0.5f,  0.5f,
		-0.5f,  0.5f  
	};

    uint32_t indices[]
    {
        0, 1, 2,
        2, 3, 0
    };

    glGenVertexArrays(1, &vao);

    if (vao == 0)
    {
        SDL_LogError(
            SDL_LOG_CATEGORY_GPU,
            "Failed to create VAO"
        );

        return false;
    }

    glBindVertexArray(vao);

    //vertex buffer object -> takes vertex data
    glGenBuffers(1, &vbo);

    if (vbo == 0)
    {
        SDL_LogError(
            SDL_LOG_CATEGORY_VIDEO,
            "Failed to create VBO"
        );

        return false;
    }

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);

    if (ebo == 0)
    {
        SDL_LogError(
            SDL_LOG_CATEGORY_VIDEO,
            "Failed to create EBO"
        );

        return false;
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);

    glEnableVertexAttribArray(0);

    glBindVertexArray(0);


	return true;
}

auto gep::renderers::renderer2d::Begin() noexcept -> void
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

auto gep::renderers::renderer2d::DrawQuad() noexcept -> void
{

	shaders::shader::instance().Bind();


	glBindVertexArray(vao);

    // In render loop:
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);


	shaders::shader::instance().Unbind();

}

auto gep::renderers::renderer2d::End(SDL_Window* window) noexcept -> void
{
    if (!SDL_GL_SwapWindow(window))
    {
        SDL_LogError(
            SDL_LOG_CATEGORY_VIDEO,
            "Failed to swap OpenGL window: %s",
            SDL_GetError()
        );
    }
}

auto gep::renderers::renderer2d::Delete() noexcept -> void
{
    if (ebo != 0)
    {
        glDeleteBuffers(1, &ebo);
        ebo = 0;
    }

    if (vbo != 0)
    {
        glDeleteBuffers(1, &vbo);
        vbo = 0;
    }

    if (vao != 0)
    {
        glDeleteVertexArrays(1, &vao);
        vao = 0;
    }

}
