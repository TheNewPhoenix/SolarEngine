
#include "wrap_window.h"
#include "Window.h"
#include "../core/Context.h"

namespace py = pybind11;

namespace solar
{

	void wrap_window(py::module &m)
	{
		py::module WindowModule = m.def_submodule("Window", "Window submodule");

		py::class_<Window::WindowSettings>(WindowModule, "WindowSettings")
			.def(py::init<>())
			.def_readwrite("fullscreen", &Window::WindowSettings::fullscreen)
			.def_readwrite("vsync", &Window::WindowSettings::vsync)
			.def_readwrite("msaa", &Window::WindowSettings::msaa)
			.def_readwrite("resizable", &Window::WindowSettings::resizable)
			.def_readwrite("minwidth", &Window::WindowSettings::minwidth)
			.def_readwrite("minheight", &Window::WindowSettings::minheight)
			.def_readwrite("borderless", &Window::WindowSettings::borderless)
			.def_readwrite("centered", &Window::WindowSettings::centered)
			.def_readwrite("display", &Window::WindowSettings::display)
			.def_readwrite("highdpi", &Window::WindowSettings::highdpi)
			.def_readwrite("refreshrate", &Window::WindowSettings::refreshrate)
			.def_readwrite("useposition", &Window::WindowSettings::useposition)
			.def_readwrite("x", &Window::WindowSettings::x)
			.def_readwrite("y", &Window::WindowSettings::y);

		py::class_<Window>(WindowModule, "Window")
			.def(py::init<Context*>())
			.def("createWindow", &Window::createWindow, "creates the window", py::arg("width") = 800, py::arg("height") = 600, py::arg("settings") = Window::WindowSettings())
			.def("shouldClose", &Window::shouldClose, "returns if the window is closing")
			.def("close", &Window::close, "closes the window")
			.def("setTitle", &Window::setTitle, "sets the window title", py::arg("title"))
			.def("getPosition", &Window::getPosition, "returns current window position")
			.def("setPosition", &Window::setPosition, "sets the window position", py::arg("x"), py::arg("y"))
			.def("getSize", &Window::getSize, "returns the size of the window")
			.def("setSize", &Window::setSize, "sets the size of the window", py::arg("width"), py::arg("height"))
			.def("getCursorPosition", &Window::getCursorPosition, "returns the cursor position")
			.def("setCursorPosition", &Window::setCursorPosition, "sets the cursor position", py::arg("x"), py::arg("y"))
			.def("maximize", &Window::maximize, "maximizes the window")
			.def("iconify", &Window::iconify, "minimizes the window")
			.def("restore", &Window::restore, "restores the window")
			.def("show", &Window::show, "shows the window")
			.def("hide", &Window::hide, "hides the window")
			.def("focus", &Window::focus, "focuses the window")
			.def("swapBuffers", &Window::swapBuffers, "swaps window buffers")
			.def("pollEvents", &Window::pollEvents, "poll window events")
			.def("makeContextCurrent", &Window::makeContextCurrent, "makes the context current");
	}

}