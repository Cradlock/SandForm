
# Настройки проекта
cmake_minimum_required(VERSION 3.15)

project(sandform)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)



# Папка, куда будут падать все скомпилированные .dll и .exe
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Подключение зависимостей
find_package(nlohmann_json REQUIRED)


# Подключение исполняемого файла
add_executable(app all/app.cpp) 



# Подключение ресурсов к бинарнику
add_custom_command(
    TARGET app             # The target the command is attached to
    POST_BUILD             # The command runs after MyTarget is built
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/resources"
            "$<TARGET_FILE_DIR:app>" # Use generator expression for config-specific path
    COMMENT "Copying resources for app"
)


# Активация модулей 
add_subdirectory(all/core)
add_subdirectory(all/plugin_manager)
add_subdirectory(all/logic)


# Подключение core и plugin_manager
target_link_libraries(app PRIVATE 
  core 
  plugin_manager
)


# Подключение зависимостей
target_link_libraries(plugin_manager PUBLIC nlohmann_json::nlohmann_json)







# Подключение nvim
if(CMAKE_EXPORT_COMPILE_COMMANDS)
set(SOURCE_FILE "${CMAKE_BINARY_DIR}/compile_commands.json")
set(DESTINATION_FILE "${CMAKE_SOURCE_DIR}/compile_commands.json")

if(NOT EXISTS ${DESTINATION_FILE})
    execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${SOURCE_FILE} ${DESTINATION_FILE})
endif()

endif()


# Вставка базовых модулей
if(MINGW)
    # Список стандартных DLL, которые нужны MinGW программам
    set(MINGW_LIBS libstdc++-6.dll libgcc_s_seh-1.dll libwinpthread-1.dll)

    foreach(LIB_NAME ${MINGW_LIBS})
        # Находим, все файлы
        find_file(LIB_PATH_${LIB_NAME} NAMES ${LIB_NAME} PATHS "/usr/x86_64-w64-mingw32/bin" "/usr/lib/gcc/x86_64-w64-mingw32/bin")
        
        if(LIB_PATH_${LIB_NAME})
            add_custom_command(TARGET app POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different "${LIB_PATH_${LIB_NAME}}" "$<TARGET_FILE_DIR:app>"
                COMMENT "Copying ${LIB_NAME} to output directory"
            )
        endif()

    endforeach()

endif()




