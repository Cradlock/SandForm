set(CORE_SOURCES
  src/config/config.cpp  
  src/log/log.cpp 
  src/tick/tick.cpp 
  src/engine.cpp 
  src/eventbus/eventbus.cpp
  src/resources/main.cpp
  src/utils/general.cpp 
  src/resources/types/json.cpp
)


add_library(core SHARED ${CORE_SOURCES})


target_include_directories(core PUBLIC 
  include 
)

find_package(nlohmann_json CONFIG REQUIRED)

target_link_libraries(core PRIVATE nlohmann_json::nlohmann_json)



