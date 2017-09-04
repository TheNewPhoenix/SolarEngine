cmake_minimum_required(VERSION 2.8.12)
project(SolarEngine)

ADD_DEFINITIONS(-DGLEW_STATIC -DSOLAR_LOGGING)

list(APPEND CMAKE_PREFIX_PATH "$ENV{PROGRAMFILES}/GLEW")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules/")

find_package(Assimp REQUIRED)
include_directories(${ASSIMP_INCLUDE_DIRS})
link_libraries(${ASSIMP_LIBRARIES})

find_package(pybind11 REQUIRED)
include_directories(${pybind11_INCLUDE_DIRS})
link_libraries(${pybind11_LIBRARIES})

find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

find_package(opengl REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
link_libraries(${OPENGL_LIBRARIES})

set(SDL2_PATH "$ENV{PROGRAMFILES}/SDL2")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
link_libraries(${SDL2_LIBRARY})

find_package(STB REQUIRED)
include_directories(${STB_INCLUDE_DIR})

set(SOLAR_CORE_SRCS
		src/solar/core/Application.cpp
		src/solar/core/Application.h
		src/solar/core/Context.cpp
		src/solar/core/Context.h
		src/solar/core/Engine.cpp
		src/solar/core/Engine.h
		src/solar/core/Object.cpp
		src/solar/core/Object.h
		src/solar/core/Timer.cpp
		src/solar/core/Timer.h
)

set(SOLAR_GRAPHICS_SRCS
		src/solar/graphics/Camera.cpp
		src/solar/graphics/Camera.h
		src/solar/graphics/Color.cpp
		src/solar/graphics/Color.h
		src/solar/graphics/Graphics.cpp
		src/solar/graphics/Graphics.h
		src/solar/graphics/Mesh.cpp
		src/solar/graphics/Mesh.h
		src/solar/graphics/StaticModel.cpp
		src/solar/graphics/StaticModel.h
		src/solar/graphics/VertexAttributes.cpp
		src/solar/graphics/VertexAttributes.h
		src/solar/graphics/opengl/Program.cpp
		src/solar/graphics/opengl/Program.h
		src/solar/graphics/opengl/Shader.cpp
		src/solar/graphics/opengl/Shader.h
		src/solar/graphics/opengl/Texture.cpp
		src/solar/graphics/opengl/Texture.h
		src/solar/graphics/opengl/VertexArray.cpp
		src/solar/graphics/opengl/VertexArray.h
		src/solar/graphics/opengl/VertexBuffer.cpp
		src/solar/graphics/opengl/VertexBuffer.h
		src/solar/graphics/shapes/Shape.cpp
		src/solar/graphics/shapes/Shape.h

)

set(SOLAR_INPUT_SRCS
		src/solar/input/Input.cpp
		src/solar/input/Input.h
)

set(SOLAR_IO_SRCS
		src/solar/io/Log.cpp
		src/solar/io/Log.h
)

set(SOLAR_MATH_SRCS
		src/solar/math/Math.h
)

set(SOLAR_RESOURCE_SRCS
		src/solar/resource/Image.cpp
		src/solar/resource/Image.h
		src/solar/resource/Model.cpp
		src/solar/resource/Model.h
)

set(Solar_SRCS
		src/solar/Types.h
		src/solar/Common.h
		${SOLAR_CORE_SRCS}
		${SOLAR_GRAPHICS_SRCS}
		${SOLAR_INPUT_SRCS}
		${SOLAR_IO_SRCS}
		${SOLAR_MATH_SRCS}
		${SOLAR_RESOURCE_SRCS}
)

set(SolarPy_SRCS
		src/solar/graphics/wrap_graphics.cpp
		src/solar/graphics/wrap_graphics.h
		src/solar/core/Solar_Module.cpp
)

add_library(SolarEngine STATIC ${Solar_SRCS})
target_include_directories(SolarEngine PUBLIC ${Solar_SRCS})
target_link_libraries(SolarEngine)

add_subdirectory(src/samples)

add_library(SolarEnginePy SHARED ${SolarPy_SRCS})
target_include_directories(SolarEnginePy PUBLIC ${Solar_SRCS})
target_link_libraries(SolarEnginePy PUBLIC pybind11::module SolarEngine)
set_target_properties(SolarEnginePy
	PROPERTIES PREFIX "${PYTHON_MODULE_PREFIX}"
	SUFFIX "${PYTHON_MODULE_EXTENSION}"
)

project(Game)

add_executable(Game src/solar/main/main.cpp)
include_directories("${SolarEngine_SOURCE_DIR}/src")
target_link_libraries(Game PUBLIC pybind11::embed SolarEnginePy SolarEngine)

install(TARGETS Game SolarEnginePy DESTINATION ${CMAKE_SOURCE_DIR}/bin)
install(DIRECTORY data/ DESTINATION ${CMAKE_SOURCE_DIR}/bin/data)

add_custom_command(TARGET Game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data
        $<TARGET_FILE_DIR:Game>/data)