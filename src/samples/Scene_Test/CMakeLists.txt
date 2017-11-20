
add_executable(SceneTest SceneTest.cpp)
target_link_libraries(SceneTest SolarEngine)

add_custom_command(TARGET SceneTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data
        $<TARGET_FILE_DIR:SceneTest>/data)

add_custom_command(TARGET SceneTest POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/libs
        $<TARGET_FILE_DIR:SceneTest>)

add_custom_command(TARGET SceneTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/config.json
        $<TARGET_FILE_DIR:SceneTest>/config.json)