cmake_minium_required()


project(sandform)













# Подключение nvim
if(CMAKE_EXPORT_COMPILE_COMMANDS)
set(SOURCE_FILE "${CMAKE_BINARY_DIR}/compile_commands.json")
set(DESTINATION_FILE "${CMAKE_SOURCE_DIR}/compile_commands.json")

if(NOT EXISTS ${DESTINATION_FILE})
    execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${SOURCE_FILE} ${DESTINATION_FILE})
endif()
endif()


