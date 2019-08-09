add_library(dilation2-example STATIC ${headers} dilation2-example.cpp)
add_library(demo-example STATIC ${headers} demo-example.cpp)

target_link_libraries(dilation2-example core)
target_link_libraries(demo-example core)

target_compile_definitions(dilation2-example PRIVATE "SPATIAL_DIM=2")
target_compile_definitions(demo-example PRIVATE "SPATIAL_DIM=2")
