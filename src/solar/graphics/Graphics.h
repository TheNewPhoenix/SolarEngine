#pragma once

#include <gl\glew.h>
#include <GLFW\glfw3.h>

#include "..\core\Object.h"
#include "..\io\Log.h"

namespace solar
{

	class SOLAR_API Graphics : public Object
	{
		SOLAR_OBJECT(Graphics)

	public:

		Graphics(Context* context);

		virtual ~Graphics();

		bool init();

		void enable(int capability);

		void blendFunc(int src, int dest);

		void disable(int capability);

		void clearColor(float r, float g, float b, float a);

		void clear(int buffers);

		void cullFace(int mode);

		int getWidth() const { return m_width; }

		int getHeight() const { return m_height; }

	private:
		void handleWindowResized(const char* eventType, EventParameters& params);
		int m_width, m_height;
	};

}