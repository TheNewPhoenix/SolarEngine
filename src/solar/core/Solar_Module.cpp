#include "..\graphics\wrap_graphics.h"
#include "Context.h"
#include "Object.h"
#include "Application.h"
#include "Engine.h"
#include "..\io\Log.h"

#include <pybind11\pybind11.h>
#include <pybind11\stl.h>
#include <pybind11\functional.h>
#include <boost\variant\variant.hpp>
#include <iostream>
#include <functional>

namespace py = pybind11;

PYBIND11_MODULE(SolarEnginePy, m)
{
	using namespace solar;

	m.doc() = "Complete python bindings for Solar Engine";

	py::class_<EventGroup>(m, "EventGroup")
		.def(py::init<>())
		.def("add", &EventGroup::add, "add object to event group", py::arg("object"))
		.def("remove", &EventGroup::remove, "remove object from event group", py::arg("object"))
		.def_readwrite("receivers", &EventGroup::m_receivers);

	py::class_<Context>(m, "Context")
		.def(py::init<>())
		.def("addEventReceiver", &Context::addEventReceiver, "add object to receive events", py::arg("object"), py::arg("eventType"))
		.def("removeEventReceiver", &Context::removeEventReceiver, "remove object to receive events", py::arg("object"), py::arg("eventType"))
		.def("getEventGroup", &Context::getEventGroup, "get event group for given event type", py::arg("eventType"));

	py::class_<Object> object(m, "Object");
	object.def("onEvent", &Object::onEvent, py::arg("eventType"), py::arg("parameters"));
	object.def("unsubscribeToEvent", &Object::unsubscribeToEvent, py::arg("eventType"));
	object.def("unsubscribeToAllEvents", &Object::unsubscribeToAllEvents);
	object.def("sendEvent", &Object::sendEvent, py::arg("eventType"), py::arg("parameters") = noParameters);
	object.def("getSubsystem", &Object::getSubsystem, py::arg("typeName"));

	class PyApplicationAdapter : public ApplicationAdapter
	{
	public:
		using ApplicationAdapter::ApplicationAdapter;

		void setup() override
		{
			PYBIND11_OVERLOAD_PURE(
				void,
				ApplicationAdapter,
				setup
			);
		}

		void start() override
		{
			PYBIND11_OVERLOAD_PURE(
				void,
				ApplicationAdapter,
				start
			);
		}

		void stop() override
		{
			PYBIND11_OVERLOAD_PURE(
				void,
				ApplicationAdapter,
				stop
			);
		}

		void handleUpdate(const char* eventType, EventParameters& params) override
		{
			PYBIND11_OVERLOAD_PURE(
				void,
				ApplicationAdapter,
				handleUpdate,
				eventType,
				params
			);
		}

		void handleRender(const char* eventType, EventParameters& params) override
		{
			PYBIND11_OVERLOAD_PURE(
				void,
				ApplicationAdapter,
				handleRender,
				eventType,
				params
			);
		}
	};

	py::class_<ApplicationAdapter, PyApplicationAdapter>(m, "ApplicationAdapter", object)
		.def(py::init<Context*>())
		.def("setup", &ApplicationAdapter::setup)
		.def("start", &ApplicationAdapter::start)
		.def("stop", &ApplicationAdapter::stop)
		.def("handleUpdate", &ApplicationAdapter::handleUpdate, py::arg("eventType"), py::arg("params"))
		.def("handleRender", &ApplicationAdapter::handleRender, py::arg("eventType"), py::arg("params"));

	py::class_<Application>(m, "Application", object)
		.def(py::init<Context*, ApplicationAdapter*>())
		.def("run", &Application::run);

	py::class_<Log>(m, "Logger")
		.def_static("log_info", &Log::write, py::arg("level") = solar::LOG_INFO, py::arg("message"))
		.def_static("log_debug", &Log::write, py::arg("level") = solar::LOG_DEBUG, py::arg("message"))
		.def_static("log_error", &Log::write, py::arg("level") = solar::LOG_ERROR, py::arg("message"))
		.def_static("log_warning", &Log::write, py::arg("level") = solar::LOG_WARNING, py::arg("message"));
	solar::wrap_graphics(m, object);
}
