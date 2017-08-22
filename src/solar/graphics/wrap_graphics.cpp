
#include "wrap_graphics.h"
#include "Graphics.h"
#include "opengl\VertexArray.h"
#include "opengl\VertexBuffer.h"
#include "shapes\Shape.h"
#include "..\core\Context.h"

namespace py = pybind11;

namespace solar
{
	
	void wrap_graphics(py::module &m, py::class_<Object>& object)
	{
		m.def("getGraphics", Graphics::getTypeNameStatic);

		py::module GraphicsModule = m.def_submodule("Graphics");

		py::class_<Graphics>(GraphicsModule, "Graphics", object)
			.def(py::init<Context*>())
			.def("enable", &Graphics::enable, py::arg("caps"))
			.def("blendFunc", &Graphics::blendFunc, py::arg("src"), py::arg("dest"))
			.def("disable", &Graphics::disable, py::arg("caps"))
			.def("clearColor", &Graphics::clearColor, py::arg("r"), py::arg("g"), py::arg("b"), py::arg("a"))
			.def("clear", &Graphics::clear, py::arg("buffers"))
			.def("cullFace", &Graphics::cullFace, py::arg("mode"));

		py::class_<VertexBuffer>(GraphicsModule, "VertexBuffer")
			.def(py::init<int>())
			.def("setData", &VertexBuffer::setData,py::arg("size"), py::arg("data"), py::arg("usage"))
			.def("resize", &VertexBuffer::resize, py::arg("size"), py::arg("usage"))
			.def("setSubData", &VertexBuffer::setSubData, py::arg("offset"), py::arg("size"), py::arg("data"))
			.def("bind", &VertexBuffer::bind)
			.def("unbind", &VertexBuffer::unbind);

		py::class_<VertexArray>(GraphicsModule, "VertexArray")
			.def(py::init<>())
			.def("bind", &VertexArray::bind)
			.def("unbind", &VertexArray::unbind)
			.def("enableAttributeArray", &VertexArray::enableAttributeArray, py::arg("index"))
			.def("disableAttributeArray", &VertexArray::disableAttributeArray, py::arg("index"))
			.def("pointAttribute", &VertexArray::pointAttribute, py::arg("index"), py::arg("count"), py::arg("type"), py::arg("normalized") = false, py::arg("stride") = 0, py::arg("offset") = 0);

		py::class_<Shape>(GraphicsModule, "Shape")
			.def(py::init<>())
			.def("render", &Shape::render);
	}

}