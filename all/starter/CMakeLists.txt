# Настройки проекта
cmake_minimum_required(VERSION 3.15)

project(sandform_builder)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Определение ОС
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
if(WIN32 OR CMAKE_SYSTEM_NAME STREQUAL "Windows")
  set(TARGET_OS "windows")
else()
  set(TARGET_OS "linux")
endif()

# Разрядность
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(TARGET_ARCH "x64")
else()
    set(TARGET_ARCH "x86")
endif()

# Задаем базовый путь к папке инструментов движка
set(RELATIVE_BIN_DIR "engine/tools/bin/${TARGET_OS}/${TARGET_ARCH}")
set(LOCAL_TOOLS_BIN_DIR "${CMAKE_SOURCE_DIR}/../${RELATIVE_BIN_DIR}")

# Папка, куда будут падать все скомпилированные .dll и .exe
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${LOCAL_TOOLS_BIN_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${LOCAL_TOOLS_BIN_DIR}/libs")
# Подключение исполняемого файла
add_executable(app app.cpp) 

add_library(engine_sdk INTERFACE)

target_include_directories(engine_sdk INTERFACE "${CMAKE_SOURCE_DIR}/../sdk")


# Активация модулей 
add_subdirectory(static/plugin_manager)
add_subdirectory(dynamic/logic)
add_subdirectory(dynamic/core)


# Подключение core и plugin_manager
target_link_libraries(app PRIVATE 
  core 
  plugin_manager
  logic
)

# Вставка базовых модулей для Windows (MinGW)
if(MINGW)
    set(MINGW_LIBS libstdc++-6.dll libgcc_s_seh-1.dll libwinpthread-1.dll)

    foreach(LIB_NAME ${MINGW_LIBS})
        # Ищем библиотеки в путях кросс-компилятора Linux (для x64 и x86)
        find_file(LIB_PATH_${LIB_NAME} NAMES ${LIB_NAME} 
            PATHS "/usr/x86_64-w64-mingw32/bin" 
                  "/usr/lib/gcc/x86_64-w64-mingw32/bin"
                  "/usr/i686-w64-mingw32/bin"
        )
        
        if(LIB_PATH_${LIB_NAME})
            # Ситуация 1: Копирование при обычной сборке (POST_BUILD)
            add_custom_command(TARGET app POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different "${LIB_PATH_${LIB_NAME}}" "$<TARGET_FILE_DIR:app>"
                COMMENT "Copying ${LIB_NAME} to local build directory"
            )

            # Ситуация 2: Копирование при cmake --install
            install(FILES "${LIB_PATH_${LIB_NAME}}" DESTINATION "${RELATIVE_BIN_DIR}")
        endif()
    endforeach()
endif()

# Настройка путей поиска библиотек (RPATH) для Linux
if(UNIX AND NOT APPLE)
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

    # Важно: $ORIGIN для работы внутри папки сборки, и $ORIGIN/libs для работы после инсталляции
    set_target_properties(app PROPERTIES 
        INSTALL_RPATH "$ORIGIN:$ORIGIN/libs"
        BUILD_WITH_INSTALL_RPATH TRUE
    )
endif()


# Подключение nvim
if(CMAKE_EXPORT_COMPILE_COMMANDS)
set(SOURCE_FILE "${CMAKE_BINARY_DIR}/compile_commands.json")
set(DESTINATION_FILE "${CMAKE_SOURCE_DIR}/compile_commands.json")

if(NOT EXISTS ${DESTINATION_FILE})
    execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${SOURCE_FILE} ${DESTINATION_FILE})
endif()

endif()

install(TARGETS app core logic
    RUNTIME DESTINATION "${RELATIVE_BIN_DIR}"                 # Сюда улетят .exe и .dll
    LIBRARY DESTINATION "${RELATIVE_BIN_DIR}/libs"            # Сюда улетят Linux .so файлы
    ARCHIVE DESTINATION "${RELATIVE_BIN_DIR}/libs"            # Сюда улетят Windows .lib файлы импорта
)


