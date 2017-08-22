#pragma once

#include <pybind11\pybind11.h>

#include "../core/Object.h"

namespace py = pybind11;

namespace solar
{

	void wrap_window(py::module &m);

}