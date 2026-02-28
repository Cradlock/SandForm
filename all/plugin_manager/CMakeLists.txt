set(SOURCES
  src/manager.cpp
  src/plugin.cpp
)



# Настройки для boost 
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)

find_package(Boost 1.70 REQUIRED COMPONENTS dll)


add_library(plugin_manager STATIC ${SOURCES})




target_include_directories(plugin_manager PUBLIC include)
target_include_directories(plugin_manager PRIVATE ${Boost_INCLUDE_DIRS})


# Связь с core 
target_link_libraries(plugin_manager PRIVATE core)
# Связь с Boost.DLL 
target_link_libraries(plugin_manager PRIVATE ${Boost_LIBRARIES})





