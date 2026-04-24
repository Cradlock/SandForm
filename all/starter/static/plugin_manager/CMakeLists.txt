set(SOURCES
  src/manager.cpp 
)


add_library(plugin_manager STATIC ${SOURCES})

target_include_directories(plugin_manager PUBLIC include)


find_package(RapidJSON CONFIG REQUIRED)

target_link_libraries(plugin_manager PUBLIC engine_sdk)
target_link_libraries(plugin_manager PUBLIC rapidjson)



