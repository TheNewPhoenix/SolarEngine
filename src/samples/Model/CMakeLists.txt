
add_executable(ModelTest ModelTest.cpp)
target_link_libraries(ModelTest SolarEngine)

add_custom_command(TARGET ModelTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data
        $<TARGET_FILE_DIR:ModelTest>/data)

add_custom_command(TARGET ModelTest POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/libs
        $<TARGET_FILE_DIR:ModelTest>)