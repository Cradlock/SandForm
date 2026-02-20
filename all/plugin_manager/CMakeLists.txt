set(SOURCES
  src/manager.cpp
)


add_library(plugin_manager STATIC ${SOURCES})


target_include_directories(plugin_manager PUBLIC include)
