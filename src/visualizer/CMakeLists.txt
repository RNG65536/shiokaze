add_library(gridvisualizer2 STATIC ${headers} gridvisualizer2.cpp)
add_library(gridvisualizer3 STATIC ${headers} gridvisualizer3.cpp)
add_library(macvisualizer2 STATIC ${headers} macvisualizer2.cpp)
add_library(macvisualizer3 STATIC ${headers} macvisualizer3.cpp)

target_link_libraries(gridvisualizer2 core)
target_link_libraries(gridvisualizer3 core)
target_link_libraries(macvisualizer2 core)
target_link_libraries(macvisualizer3 core)

target_compile_definitions(gridvisualizer2 PRIVATE "SPATIAL_DIM=2")
target_compile_definitions(gridvisualizer3 PRIVATE "SPATIAL_DIM=3")
target_compile_definitions(macvisualizer2 PRIVATE "SPATIAL_DIM=2")
target_compile_definitions(macvisualizer3 PRIVATE "SPATIAL_DIM=3")
