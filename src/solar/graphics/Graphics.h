#pragma once

#include <gl\glew.h>
//#include <GLFW\glfw3.h>
#include <SDL.h>
#include <glm\glm.hpp>

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

		bool toggleFullscreen();

		void beginFrame();

		void endFrame();

		void enable(int capability);

		void blendFunc(int src, int dest);

		void disable(int capability);

		void clearColor(float r, float g, float b, float a);

		void clear(int buffers);

		void cullFace(int mode);

		bool isInitialized() const;
		
		SDL_Window* getWindow() const { return m_window; }

		const std::string& getTitle() const { return m_title; }

		glm::ivec2 getWindowPosition() const;

		int getWidth() const { return m_width; }

		int getHeight() const { return m_height; }

		bool isFullscreen() const { return m_fullscreen; }

		bool isBorderless() const { return m_borderless; }

		bool isResizable() const { return m_resizable; }

		bool isVSync() const { return m_vsync; }

		int getRefreshRate() const { return m_refreshRate; }

		int getMonitor() const { return m_monitor; }

	private:

		SDL_GLContext m_context;
		SDL_Window* m_window;

		std::string m_title;
		int m_width;
		int m_height;
		glm::ivec2 m_position;
		bool m_fullscreen;
		bool m_borderless;
		bool m_resizable;
		bool m_vsync;
		int m_refreshRate;
		int m_monitor;
	};

}