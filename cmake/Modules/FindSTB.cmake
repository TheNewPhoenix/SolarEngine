# Try to find STB include path.
# Once done this will define
#
# STB_FOUND
# STB_INCLUDE_DIR
#

find_path( STB_INCLUDE_DIR 
    NAMES
        stb/stb.h
    HINTS
        "${STB_LOCATION}/stb"
        "$ENV{STB_LOCATION}/stb"
    PATHS
        "$ENV{PROGRAMFILES}/stb"
        "${STB_INCLUDE_DIR}"
        /usr/openwin/share/include
        /usr/openwin/include
        /usr/X11R6/include
        /usr/include/X11
        /opt/graphics/OpenGL/include
        /opt/graphics/OpenGL/contrib/libglfw
        /usr/local/include
        /usr/include/GL
        /usr/include
    DOC 
        "The directory where stb/stb.h resides"
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(STB 
    REQUIRED_VARS
        STB_INCLUDE_DIR
)

mark_as_advanced(
  GLFW_INCLUDE_DIR
)