add_library(macbackwardflip2 STATIC ${headers} macbackwardflip2.cpp)
add_library(macbackwardflip3 STATIC ${headers} macbackwardflip3.cpp)

target_link_libraries(macbackwardflip2 core)
target_link_libraries(macbackwardflip3 core)

target_compile_definitions(macbackwardflip2 PRIVATE "SPATIAL_DIM=2")
target_compile_definitions(macbackwardflip3 PRIVATE "SPATIAL_DIM=3")
