set(CORE_SOURCES
  src/config/config_init.cpp  
  src/config/config_api.cpp  
  src/config/config_utils.cpp  

  
  src/log/log.cpp 
  
  src/tick/tick_init.cpp 
  
  src/engine.cpp 
  
  src/eventbus/eventbus_init.cpp
  src/eventbus/eventbus_api.cpp
  
  src/utils/general.cpp 
  src/utils/programm.cpp 
  

  src/resources/resources_api.cpp
  src/resources/resources_init.cpp
  src/resources/resources_iresource.cpp
  src/resources/resources_thread.cpp
  src/resources/resources_utils.cpp
  src/resources/resources_task.cpp
  
  src/resources/types/json.cpp
  src/resources/types/texture.cpp
)


add_library(core SHARED ${CORE_SOURCES})


target_include_directories(core PUBLIC 
  include 
)


find_package(RapidJSON CONFIG REQUIRED)

target_link_libraries(core PUBLIC rapidjson)



