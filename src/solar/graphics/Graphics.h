#pragma once

#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include <SDL.h>

#include "..\core\Object.h"
#include "..\io\Log.h"
#include "..\resource\Image.h"

namespace solar
{

	class SOLAR_API Graphics : public Object
	{
		SOLAR_OBJECT(Graphics)

	public:

		Graphics(Context* context);

		virtual ~Graphics();

		void setWindowTitle(const char* title);

		void setWindowIcon(Image* image);

		void setWindowPosition(int x, int y);

		bool setMode(int width, int height, bool fullscreen, bool borderless, bool resizable, bool vsync, int monitor, int refreshRate);

		bool setMode(int width, int height);

		void enable(int capability);

		void blendFunc(int src, int dest);

		void disable(int capability);

		void clearColor(float r, float g, float b, float a);

		void clear(int buffers);

		void cullFace(int mode);

		int getWidth() const { return m_width; }

		int getHeight() const { return m_height; }

		bool isInitialized() const;

	private:
		int m_width;
		int m_height;
		bool m_fullscreen;
		bool m_borderless;
		bool m_resizable;
		bool m_vsync;

		SDL_GLContext m_context;
		SDL_Window* m_window;

		std::string m_title;
	};

}