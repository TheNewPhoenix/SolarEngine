#include <pybind11\pybind11.h>
#include <pybind11\embed.h>
#include <pybind11\eval.h>
#include <iostream>

#include <solar\Common.h>
#include <solar\Types.h>

#include <solar\io\Log.h>

namespace py = pybind11;

int main(int argc, char *argv[] )
{
	#ifdef _EXPORTING
	std::cout << "exporting" << std::endl;
	#endif // _EXPORTING

	int errorCode = EXIT_SUCCESS;

	if (argc > 1)
	{
		py::scoped_interpreter guard{};

		py::object scope = py::module::import("__main__").attr("__dict__");

		const char* filepath = argv[1];
		std::cout << "Loading python file from: " << filepath << std::endl;

		try 
		{
			py::eval_file(filepath, scope);
		}
		catch (std::exception e)
		{
			std::cout << "Could not execute python script: " << filepath << std::endl;
			std::cout << "\t" << e.what() << std::endl;
			errorCode = EXIT_FAILURE;
		}

	}
	else
	{
		std::cout << "No arguments" << std::endl;
		std::getchar();
		return EXIT_FAILURE;
	}
	return errorCode;
}