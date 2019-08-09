add_library(macpressuresolver2 STATIC ${headers} macpressuresolver2.cpp)
add_library(macpressuresolver3 STATIC ${headers} macpressuresolver3.cpp)
add_library(macstreamfuncsolver2 STATIC ${headers} macstreamfuncsolver2.cpp)
add_library(macstreamfuncsolver3 STATIC ${headers} macstreamfuncsolver3.cpp)

target_link_libraries(macpressuresolver2 core)
target_link_libraries(macpressuresolver3 core)
target_link_libraries(macstreamfuncsolver2 core)
target_link_libraries(macstreamfuncsolver3 core)

target_compile_definitions(macpressuresolver2 PRIVATE "SPATIAL_DIM=2")
target_compile_definitions(macpressuresolver3 PRIVATE "SPATIAL_DIM=3")
target_compile_definitions(macstreamfuncsolver2 PRIVATE "SPATIAL_DIM=2")
target_compile_definitions(macstreamfuncsolver3 PRIVATE "SPATIAL_DIM=3")
