#include "texture_2d.hpp"
#include <glad/gl.h>
#include <SDL3_image/SDL_image.h>

namespace gep::renderer
{
	texture_2d::texture_2d(const char* t_path)
	{
		auto img_file = IMG_Load(t_path);
		if (!img_file)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
				"Image failed to load: %s", SDL_GetError());
			return;
		}

		auto rgba_file = SDL_ConvertSurface(img_file, SDL_PIXELFORMAT_RGBA32);
		SDL_DestroySurface(img_file);
		if (!rgba_file)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
				"Image format conversion failed: %s", SDL_GetError());
			return;
		}

		SDL_FlipSurface(rgba_file, SDL_FLIP_VERTICAL);

		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(
			GL_TEXTURE_2D, 0, GL_RGBA,
			rgba_file->w, rgba_file->h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, rgba_file->pixels);

		glGenerateMipmap(GL_TEXTURE_2D);

		width = rgba_file->w;
		height = rgba_file->h;

		SDL_DestroySurface(rgba_file);
	}

	texture_2d::texture_2d(texture_2d&& rhs) noexcept : id(std::exchange(rhs.id, 0))
	{

	}

	texture_2d::~texture_2d()
	{
		clear();
	}

	auto texture_2d::bind() const noexcept -> void
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, id);
	}

	auto texture_2d::clear() -> void
	{
		if (id != 0)
		{
			glDeleteTextures(1, &id);
			id = 0;
		}
	}

	texture_2d& texture_2d::operator=(texture_2d&& rhs) noexcept
	{
		if (this == &rhs)
		{
			return *this;
		}

		clear();

		id = std::exchange(rhs.id, 0);
	}

}