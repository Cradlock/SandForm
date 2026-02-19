cmake_minimum_required(VERSION 3.15)

project(sandform)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_subdirectory(all/core)
add_subdirectory(all/input)
add_subdirectory(all/logic)
add_subdirectory(all/modding)
add_subdirectory(all/render)
add_subdirectory(all/plugin_manager)
add_subdirectory(all/sound)
add_subdirectory(all/ui)

add_executable(app all/app.cpp) 


# Подключение nvim
if(CMAKE_EXPORT_COMPILE_COMMANDS)
set(SOURCE_FILE "${CMAKE_BINARY_DIR}/compile_commands.json")
set(DESTINATION_FILE "${CMAKE_SOURCE_DIR}/compile_commands.json")

if(NOT EXISTS ${DESTINATION_FILE})
    execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${SOURCE_FILE} ${DESTINATION_FILE})
endif()
endif()


