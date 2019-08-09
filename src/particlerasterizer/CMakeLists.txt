add_library(flatrasterizer2 STATIC ${headers} flatrasterizer2.cpp)
add_library(flatrasterizer3 STATIC ${headers} flatrasterizer3.cpp)
add_library(convexhullrasterizer2 STATIC ${headers} convexhullrasterizer2.cpp)
add_library(convexhullrasterizer3 STATIC ${headers} convexhullrasterizer3.cpp)

target_link_libraries(flatrasterizer2 core)
target_link_libraries(flatrasterizer3 core)
target_link_libraries(convexhullrasterizer2 core)
target_link_libraries(convexhullrasterizer3 core)

target_compile_definitions(flatrasterizer2 PRIVATE "SPATIAL_DIM=2")
target_compile_definitions(flatrasterizer3 PRIVATE "SPATIAL_DIM=3")
target_compile_definitions(convexhullrasterizer2 PRIVATE "SPATIAL_DIM=2")
target_compile_definitions(convexhullrasterizer3 PRIVATE "SPATIAL_DIM=3")
