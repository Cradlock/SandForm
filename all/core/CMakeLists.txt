set(CORE_SOURCES
  src/config.cpp 
  src/log.cpp 
  src/tick.cpp 
  src/engine.cpp 
  src/eventbus.cpp
  src/resources.cpp
  src/utils.cpp 

)


add_library(core SHARED ${CORE_SOURCES})


target_include_directories(core PUBLIC 
  include 
)



