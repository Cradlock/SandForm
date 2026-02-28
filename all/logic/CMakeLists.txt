set(SOURCES
  src/table/table.cpp 
)


add_library(logic SHARED ${SOURCES})



target_include_directories(logic PUBLIC include)

# Связь с core 
target_link_libraries(logic PRIVATE core)




