add_library(pointgridhash2 STATIC ${headers} pointgridhash2.cpp)
add_library(pointgridhash3 STATIC ${headers} pointgridhash3.cpp)

target_link_libraries(pointgridhash2 core)
target_link_libraries(pointgridhash3 core)

target_compile_definitions(pointgridhash2 PRIVATE "SPATIAL_DIM=2")
target_compile_definitions(pointgridhash3 PRIVATE "SPATIAL_DIM=3")
