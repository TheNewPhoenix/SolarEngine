#include "Graphics.h"
#include "..\io\Log.h"

namespace solar
{
	Graphics::Graphics(Context* context) :
		Object(context),
		m_context(0),
		m_window(0),
		m_width(0),
		m_height(0),
		m_fullscreen(false),
		m_borderless(false),
		m_resizable(false),
		m_vsync(false),
		m_monitor(0),
		m_refreshRate(0)
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
			SOLAR_LOGERROR() << "SDL could not initialize! SDL Error: " << SDL_GetError();
		SOLAR_LOGINFO() << "Initializing graphics";
	}

	Graphics::~Graphics()
	{
		SOLAR_LOGINFO() << "Terminating Graphics";

		//Destroy window	
		SDL_DestroyWindow(m_window);
		m_window = NULL;

		SDL_GL_DeleteContext(m_context);

		//Quit SDL subsystems
		SDL_Quit();
	}

	bool Graphics::setMode(int width, int height, bool fullscreen, bool borderless, bool resizable, bool vsync, int monitor, int refreshRate)
	{
		int monitors = SDL_GetNumVideoDisplays();
		if (monitor >= monitors || monitor < 0)
			monitor = 0;

		if (fullscreen || borderless)
			resizable = false;

		if (borderless)
			fullscreen = false;

		if (!m_context)
		{
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

			unsigned flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
			if (fullscreen)
				flags |= SDL_WINDOW_FULLSCREEN;
			if (borderless)
				flags |= SDL_WINDOW_BORDERLESS;
			if (resizable)
				flags |= SDL_WINDOW_RESIZABLE;
			
			SOLAR_LOGDEBUG() << "Creating window";
			m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
			if (!m_window)
			{
				SOLAR_LOGERROR() << "Window could not be created! SDL Error: " << SDL_GetError();
				return false;
			}
			
			SOLAR_LOGDEBUG() << "Creating gl context";
			m_context = SDL_GL_CreateContext(m_window);
			if (!m_context)
			{
				SOLAR_LOGERROR() << "OpenGL context could not be created! SDL Error: " << SDL_GetError();
				return false;
			}

			SOLAR_LOGDEBUG() << "Initializing GLEW";
			GLenum glewError = glewInit();
			if (glewError != GLEW_OK)
			{
				SOLAR_LOGERROR() << "Error initializing GLEW! " << glewGetErrorString(glewError);
				return false;
			}
		}

		SDL_GL_SetSwapInterval(vsync ? 1 : 0);

		m_fullscreen = fullscreen;
		m_borderless = borderless;
		m_resizable = resizable;
		m_vsync = vsync;
		m_monitor = monitor;
		m_refreshRate = refreshRate;

		SDL_GL_GetDrawableSize(m_window, &m_width, &m_height);
		if (!fullscreen)
			SDL_GetWindowPosition(m_window, &m_position.x, &m_position.y);

		clearColor(0.0f, 0.0f, 0.0f, 1.0f);
		SDL_GL_SwapWindow(m_window);

		#ifdef SOLAR_LOGGING
		SOLAR_LOGINFO() << "Screen mode set with dimensions " << m_width << "x" << m_height 
			<< " and properties: " << (m_fullscreen ? "fullscreen" : "windowed")
			<< ", monitor: " << m_monitor;
		#endif // SOLAR_LOGGING

		return true;
	}

	bool Graphics::setMode(int width, int height)
	{
		return setMode(width, height, m_fullscreen, m_borderless, m_resizable, m_vsync, m_monitor, m_refreshRate);
	}

	void Graphics::setWindowTitle(const char* title) 
	{
		m_title = title;
	}

	void Graphics::beginFrame()
	{
		if (!isInitialized())
			return;

		enable(GL_DEPTH_TEST);
	}

	void Graphics::endFrame()
	{
		if (!isInitialized())
			return;

		SDL_GL_SwapWindow(m_window);
	}

	bool Graphics::isInitialized() const
	{
		return m_window != 0;
	}

	void Graphics::enable(int capability)
	{
		glEnable(capability);
	}

	void Graphics::blendFunc(int src, int dest)
	{
		glBlendFunc(src, dest);
	}

	void Graphics::disable(int capability)
	{
		glDisable(capability);
	}

	void Graphics::clearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void Graphics::clear(int buffers)
	{
		glClear(buffers);
	}

	void Graphics::cullFace(int mode)
	{
		glCullFace(mode);
	}

}