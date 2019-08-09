add_library(box2d_rigidworld2 STATIC ${headers} box2d_rigidworld2.cpp)
add_library(bullet3_rigidworld3 STATIC ${headers} bullet3_rigidworld3.cpp)
add_library(reactphysics3d_rigidworld3 STATIC ${headers} reactphysics3d_rigidworld3.cpp)
add_library(hacd-dispatcher STATIC ${headers} hacd.cpp)

target_link_libraries(box2d_rigidworld2 core box2d)
target_link_libraries(bullet3_rigidworld3 core bullet3)
target_link_libraries(reactphysics3d_rigidworld3 core reactphysics3d)
target_link_libraries(hacd-dispatcher core hacd)

target_compile_definitions(box2d_rigidworld2 PRIVATE "SPATIAL_DIM=2")
target_compile_definitions(bullet3_rigidworld3 PRIVATE "SPATIAL_DIM=3")
target_compile_definitions(reactphysics3d_rigidworld3 PRIVATE "SPATIAL_DIM=3")
target_compile_definitions(macstreamfuncsolver3 PRIVATE "SPATIAL_DIM=3")
