#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\vec2.hpp>
#include <string>
#include <vector>
#include <map>

#include "../core/Object.h"

namespace solar
{

	class Window;

	namespace window
	{
		static std::unordered_map<GLFWwindow*, Window*> windowMap;
	}

	class SOLAR_API Window : public Object
	{
		SOLAR_OBJECT(Window)
	public:
		struct WindowSettings
		{
			bool fullscreen = false;
			bool vsync = true;
			int msaa = 0;
			bool resizable = false;
			int minwidth = 1;
			int minheight = 1;
			bool borderless = false;
			bool centered = true;
			int display = 0;
			bool highdpi = false;
			double refreshrate = 0.0;
			bool useposition = false;
			int x = 0;
			int y = 0;
		};

		Window(Context* context);
		virtual ~Window();

		bool createWindow(int width = 800, int height = 600, WindowSettings settings = WindowSettings());

		bool shouldClose();
		void close();

		void setTitle(std::string &title);

		glm::vec2 getPosition() const;
		void setPosition(const int x, const int y);

		glm::vec2 getSize() const;
		void setSize(const int width, const int height);

		glm::vec2 getCursorPosition() const;
		void setCursorPosition(const int x, const int y);

		void maximize();
		void iconify();
		void restore();
		void show();
		void hide();
		void focus();

		void update(const char* eventType, EventParameters& params);
		void swapBuffers();
		void pollEvents();
		void makeContextCurrent();

		static Window* getWindow(GLFWwindow* glfwWindow)
		{
			return window::windowMap[glfwWindow];
		}

		static void registerWindow(Window* window, GLFWwindow* glfwWindow);

	private:
		void initCallbacks();

		static void window_close_callback(GLFWwindow* window);
		static void window_resize_callback(GLFWwindow* window, int width, int height);

		GLFWwindow *glfwWindow;
		std::string title;
		bool m_shouldClose;
	};

} //solar
