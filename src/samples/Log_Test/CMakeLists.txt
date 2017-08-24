
add_executable(LogTest LogTest.cpp)
target_link_libraries(LogTest SolarEngine)

add_custom_command(TARGET LogTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data
        $<TARGET_FILE_DIR:LogTest>/data)

add_custom_command(TARGET LogTest POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/libs
        $<TARGET_FILE_DIR:LogTest>)