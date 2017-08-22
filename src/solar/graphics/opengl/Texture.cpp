#include "Texture.h"
#include "..\Graphics.h"

namespace solar
{
	Texture::Texture()
	{
		glGenTextures(1, &m_handle);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_handle);
	}

	void Texture::load(const char* filename)
	{
		Image image;
		image.load(filename);
		setData(image);
	}

	void Texture::setData(Image& image)
	{
		int format;
		switch (image.getComponents())
		{
		case 1:
			format = GL_LUMINANCE;
			break;

		case 2:
			format = GL_LUMINANCE_ALPHA;
			break;

		case 3:
			format = GL_RGB;
			break;

		case 4:
			format = GL_RGBA;
			break;

		default:
			assert(false);  // Should not reach here
			break;
		}

		if (image.getData())
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, format, GL_UNSIGNED_BYTE, image.getData());
			glGenerateMipmap(GL_TEXTURE_2D);
		}
	}

	void Texture::bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_handle);
	}

	void Texture::bind(unsigned unit)
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, m_handle);
	}

	void Texture::setWrap(int u, int v)
	{
		bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, u);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, v);
	}

	void Texture::setFilter(int min, int mag)
	{
		bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);
	}
}