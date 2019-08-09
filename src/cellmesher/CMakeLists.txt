add_library(marchingcubes STATIC ${headers} marchingcubes.cpp)
add_library(dualmc STATIC ${headers} dualmc.cpp)

target_link_libraries(marchingcubes core)
target_link_libraries(dualmc core)
