
add_executable(SDLTest SDLTest.cpp)
target_link_libraries(SDLTest SolarEngine)

add_custom_command(TARGET SDLTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data
        $<TARGET_FILE_DIR:SDLTest>/data)

add_custom_command(TARGET SDLTest POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/libs
        $<TARGET_FILE_DIR:SDLTest>)