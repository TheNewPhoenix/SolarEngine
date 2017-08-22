#pragma once

namespace solar
{

	class Image
	{
	public:
		Image();

		~Image();

		void load(const char* fileName);

		void setSize(int width, int height, unsigned components);
		void setData(const unsigned char* data);
		void setPixel(int x, int y, unsigned color);

		void flipVertical();
		void flipHorizontal();

		void clear(unsigned color);

		unsigned getPixel(int x, int y);

		int getWidth() const { return m_width; }
		int getHeight() const { return m_height; }
		unsigned getComponents() const { return m_components; }
		unsigned char* getData() const { return m_data; }

	private:
		static unsigned char* getImageData(const char* fileName, int& width, int& height, unsigned& components);
		static void freeImageData(unsigned char* data);

		int m_width;
		int m_height;
		unsigned m_components;
		unsigned char* m_data;
	};

}