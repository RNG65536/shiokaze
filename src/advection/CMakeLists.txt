add_library(macadvection2 STATIC ${headers} macadvection2.cpp)
add_library(macadvection3 STATIC ${headers} macadvection3.cpp)

target_link_libraries(macadvection2 core)
target_link_libraries(macadvection3 core)

target_compile_definitions(macadvection2 PRIVATE "SPATIAL_DIM=2")
target_compile_definitions(macadvection3 PRIVATE "SPATIAL_DIM=3")
