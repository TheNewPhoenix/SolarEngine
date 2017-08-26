#include "Graphics.h"
#include "..\io\Log.h"

namespace solar
{
	Graphics::Graphics(Context* context) :
		Object(context),
		m_context(0),
		m_window(0)
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
			SOLAR_LOGERROR() << "SDL could not initialize! SDL Error: " << SDL_GetError();
		SOLAR_LOGINFO() << "Initializing graphics";
	}

	Graphics::~Graphics()
	{
		SOLAR_LOGINFO() << "Terminating GLFW";
		glfwTerminate();

		//Destroy window	
		SDL_DestroyWindow(m_window);
		m_window = NULL;

		//Quit SDL subsystems
		SDL_Quit();
	}

	bool Graphics::setMode(int width, int height, bool fullscreen, bool borderless, bool resizable, bool vsync, int monitor, int refreshRate)
	{
		SOLAR_LOGDEBUG() << "Setting mode" << m_window;
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
			}
		}

		return true;
	}

	bool Graphics::setMode(int width, int height)
	{
		return true;
	}

	void Graphics::setWindowTitle(const char* title) 
	{
		m_title = title;
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