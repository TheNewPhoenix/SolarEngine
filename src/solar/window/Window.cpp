
#include "Window.h"
#include "..\io\Log.h"

#include <iostream>
#include <pybind11\pybind11.h>

namespace py = pybind11;

namespace solar
{
	Window::Window(Context* context) :
		Object(context)
	{

	}

	Window::~Window()
	{
		
	}

	bool Window::createWindow(int width, int height, WindowSettings settings)
	{
		if (!glfwInit())
		{
			SOLAR_LOGERROR("GLFW not inititialized");
		}

		glfwWindow = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
		
		if (glfwWindow == NULL)
		{
			glfwTerminate();
			return false;
		}

		registerWindow(this, glfwWindow);

		makeContextCurrent();

		if (glewInit() != GLEW_OK)
		{
			SOLAR_LOGERROR("Failed to initialize GLEW");
			return false;
		}

		initCallbacks();

		subscribeToEvent("update", SOLAR_HANDLER(Window, update));

		return true;
	}

	void Window::initCallbacks()
	{
		glfwSetWindowCloseCallback(glfwWindow, window_close_callback);
		glfwSetWindowSizeCallback(glfwWindow, window_resize_callback);
	}

	void Window::window_close_callback(GLFWwindow* window)
	{
		Window* _window = getWindow(window);
		if (_window)
			_window->close();
	}

	void Window::window_resize_callback(GLFWwindow* window, int width, int height)
	{
		Window* _window = getWindow(window);
		if (_window)
		{
			EventParameters params;
			params["width"] = width;
			params["height"] = height;
			_window->sendEvent("window_resized", params);
		}
	}

	bool Window::shouldClose()
	{
		m_shouldClose = glfwWindowShouldClose(glfwWindow);
		return m_shouldClose;
	}

	void Window::close()
	{
		sendEvent("windowclosed");
		m_shouldClose = true;
	}

	void Window::setTitle(std::string &title)
	{
		glfwSetWindowTitle(glfwWindow, title.c_str());
	}

	glm::vec2 Window::getPosition() const
	{
		int x;
		int y;
		
		glfwGetWindowPos(Window::glfwWindow, &x, &y);

		return glm::vec2(x, y);
	}

	void Window::setPosition(const int x, const int y)
	{
		glfwSetWindowPos(glfwWindow, x, y);
	}

	glm::vec2 Window::getSize() const
	{
		int width;
		int height;
		glfwGetWindowSize(glfwWindow, &width, &height);

		return glm::vec2(width, height);
	}

	void Window::setSize(const int width, const int height)
	{
		glfwSetWindowSize(glfwWindow, width, height);
	}

	glm::vec2 Window::getCursorPosition() const
	{
		int x;
		int y;
		glfwGetWindowPos(glfwWindow, &x, &y);

		return glm::vec2(x, y);
	}

	void Window::setCursorPosition(const int x, const int y)
	{
		glfwSetCursorPos(glfwWindow, x, y);
	}

	void Window::maximize()
	{
		glfwMaximizeWindow(glfwWindow);
	}

	void Window::iconify()
	{
		glfwIconifyWindow(glfwWindow);
	}

	void Window::restore()
	{
		glfwRestoreWindow(glfwWindow);
	}

	void Window::show()
	{
		glfwShowWindow(glfwWindow);
	}

	void Window::hide()
	{
		glfwHideWindow(glfwWindow);
	}

	void Window::focus()
	{
		glfwFocusWindow(glfwWindow);
	}

	void Window::update(const char* eventType, EventParameters& params)
	{
		swapBuffers();
		pollEvents();
	}

	void Window::swapBuffers()
	{
		glfwSwapBuffers(glfwWindow);
	}

	void Window::pollEvents()
	{
		glfwPollEvents();
	}	

	void Window::makeContextCurrent()
	{
		glfwMakeContextCurrent(glfwWindow);
	}

	void Window::registerWindow(Window* window, GLFWwindow* glfwWindow)
	{
		Window* _window = window::windowMap[glfwWindow];
		if (!_window)
			window::windowMap[glfwWindow] = window;
	}
}
