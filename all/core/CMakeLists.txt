set(CORE_SOURCES
  src/config.cpp 
  src/log.cpp 
  src/tick.cpp 
)


add_library(core STATIC ${CORE_SOURCES})


target_include_directories(core PUBLIC 
  include 
)



