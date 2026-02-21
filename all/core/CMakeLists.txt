set(CORE_SOURCES
  src/config.cpp 
  src/log.cpp 
  src/tick.cpp 
  src/engine.cpp 
  src/eventbus.cpp
  src/resources.cpp
  src/utils.cpp 

)

find_package(nlohmann_json CONFIG REQUIRED)


add_library(core SHARED ${CORE_SOURCES})

target_link_libraries(main PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(core PUBLIC 
  include 
)



