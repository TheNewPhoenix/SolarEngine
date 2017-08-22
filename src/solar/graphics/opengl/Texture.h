#pragma once

#include "..\..\resource\Image.h"

namespace solar
{

	class Texture
	{
	public:
		Texture();

		~Texture();

		void load(const char* filename);
		void setData(Image& image);

		int getWidth() const { return m_width; }
		int getHeight() const { return m_height; }

		void bind();
		void bind(unsigned unit);

		void setWrap(int u, int v);
		void setFilter(int min, int mag);

	private:
		int m_width;
		int m_height;
		unsigned m_handle;
	};

}