add_library(timestepper STATIC ${headers} timestepper.cpp)

target_link_libraries(timestepper core)
