#include "Graphics.h"
#include "..\io\Log.h"

namespace solar
{
	Graphics::Graphics(Context* context) :
		Object(context)
	{
		subscribeToEvent("window_resized", SOLAR_HANDLER(Graphics, handleWindowResized));
	}

	Graphics::~Graphics()
	{
		SOLAR_LOGINFO("Terminating GLFW");
		glfwTerminate();
	}

	bool Graphics::init()
	{
		SOLAR_LOGINFO("Initializing graphics");
		
		return true;
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

	void Graphics::handleWindowResized(const char* eventType, EventParameters& params)
	{
		int width = boost::get<int>(params["width"]);
		int height = boost::get<int>(params["height"]);
		m_width = width;
		m_height = height;
		glViewport(0, 0, width, height);
	}

}