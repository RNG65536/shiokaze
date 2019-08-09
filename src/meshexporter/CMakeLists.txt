add_library(meshexporter3 STATIC ${headers} meshexporter3.cpp)

target_link_libraries(meshexporter3 core zlib)
