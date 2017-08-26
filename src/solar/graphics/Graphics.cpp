#include "Graphics.h"
#include "..\io\Log.h"

namespace solar
{
	Graphics::Graphics(Context* context) :
		Object(context)
	{
	}

	Graphics::~Graphics()
	{
		SOLAR_LOGINFO() << "Terminating GLFW";
		glfwTerminate();
	}

	bool Graphics::init()
	{
		SOLAR_LOGINFO() << "Initializing graphics";
		
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

}