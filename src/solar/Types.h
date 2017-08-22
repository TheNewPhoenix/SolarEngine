#pragma once

#include "Common.h"
#include <pybind11\pybind11.h>
#include <pybind11\stl.h>
#include <boost\variant\variant.hpp>
#include <iostream>
#include <string>

namespace pybind11 {
	namespace detail {
		template <typename... Ts>
		struct type_caster<boost::variant<Ts...>> : variant_caster<boost::variant<Ts...>> {	};

		// Specifies the function used to visit the variant -- `apply_visitor` instead of `visit`
		template <>
		struct visit_helper<boost::variant> {
			template <typename... Args>
			static auto call(Args &&...args)
				-> decltype(boost::apply_visitor(std::forward<Args>(args)...)) {
				return boost::apply_visitor(std::forward<Args>(args)...);
			}
		};
	}
} // namespace pybind11::detail

namespace solar
{
	typedef signed   char Int8;
	typedef unsigned char Uint8;

	// 16 bits integer types
	typedef signed   short Int16;
	typedef unsigned short Uint16;

	// 32 bits integer types
	typedef signed   int Int32;
	typedef unsigned int Uint32;

	// 64 bits integer types
	#if defined(_MSC_VER)
	typedef signed   __int64 Int64;
	typedef unsigned __int64 Uint64;
	#else
	typedef signed   long long Int64;
	typedef unsigned long long Uint64;
	#endif

	static std::string SOLAR_ENGINE_NAME = "SolarEngine";
}