set(SOURCES
  src/manager.cpp
)


add_library(plugin_manager STATIC ${SOURCES})

# Поиск зависимостей
find_package(nlohmann_json CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS system filesystem) 



# настройка для boost.DLL
set(Boost_USE_STATIC_LIBS OFF)
if(WIN32)
    target_compile_definitions(plugin_manager PRIVATE BOOST_ALL_DYN_LINK)
endif()


target_include_directories(plugin_manager PUBLIC include)

# Связь с core 
target_link_libraries(plugin_manager PRIVATE core)



# Линковка
target_link_libraries(plugin_manager PRIVATE Boost::system Boost::filesystem)
target_link_libraries(core PRIVATE nlohmann_json::nlohmann_json)






