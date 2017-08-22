#include "Image.h"
#include "..\io\Log.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb\stb_image.h>

namespace solar
{

	Image::Image() :
		m_width(0),
		m_height(0),
		m_components(0)
	{
	}

	Image::~Image()
	{
	}

	void Image::load(const char* fileName) 
	{
		int width, height;
		unsigned components;
		unsigned char* pixelData = getImageData(fileName, width, height, components);
		if (!pixelData)
		{
			SOLAR_LOGERROR("Could not load image " + std::string(fileName) + ": " + std::string(stbi_failure_reason()));
			return;
		}
		setSize(width, height, components);
		setData(pixelData);
		freeImageData(pixelData);
	}

	void Image::setSize(int width, int height, unsigned components)
	{
		if (width == m_width && height == m_height && components == m_components)
			return;

		if (width <= 0 || height <= 0)
			return;

		if (components > 4)
			return;

		m_data = new unsigned char[width * height * components];
		m_width = width;
		m_height = height;
		m_components = components;
	}

	void Image::setData(const unsigned char* data) 
	{
		if (!m_data)
			return;

		memcpy(m_data, data, m_width * m_height * m_components);
	}

	void Image::setPixel(int x, int y, unsigned color);

	void Image::flipVertical();

	void Image::flipHorizontal();

	void Image::clear(unsigned color);

	unsigned Image::getPixel(int x, int y);

	unsigned char* Image::getImageData(const char* fileName, int& width, int& height, unsigned& components)
	{
		return stbi_load(fileName, &width, &height, (int*)&components, 0);
	}

	void Image::freeImageData(unsigned char* data)
	{
		if (!data)
			return;

		stbi_image_free(data);
	}

}