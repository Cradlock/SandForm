set(SOURCES
  src/hello.cpp 
)


add_library(logic SHARED ${SOURCES})

target_include_directories(logic PUBLIC include )

target_link_libraries(logic PRIVATE core)
target_link_libraries(logic PUBLIC engine_sdk)



