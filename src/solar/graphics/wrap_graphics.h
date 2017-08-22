#pragma once

#include <pybind11\pybind11.h>

#include "..\core\Object.h"

namespace py = pybind11;

namespace solar
{

	void wrap_graphics(py::module &m, py::class_<Object>& object);

}