add_library(macnbflip2 STATIC ${headers} macnbflip2.cpp)
add_library(macnbflip3 STATIC ${headers} macnbflip3.cpp)
add_library(macexnbflip2 STATIC ${headers} macexnbflip2.cpp)
add_library(macexnbflip3 STATIC ${headers} macexnbflip3.cpp)

target_link_libraries(macnbflip2 core)
target_link_libraries(macnbflip3 core)
target_link_libraries(macexnbflip2 macnbflip2)
target_link_libraries(macexnbflip3 macnbflip3)

target_compile_definitions(macnbflip2 PRIVATE "SPATIAL_DIM=2")
target_compile_definitions(macnbflip3 PRIVATE "SPATIAL_DIM=3")
target_compile_definitions(macexnbflip2 PRIVATE "SPATIAL_DIM=2")
target_compile_definitions(macexnbflip3 PRIVATE "SPATIAL_DIM=3")
