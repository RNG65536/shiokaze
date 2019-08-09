add_library(macliquid2 STATIC ${headers} macliquid2.cpp)
add_library(macliquid3 STATIC ${headers} macliquid3.cpp)
add_library(macflipliquid2 STATIC ${headers} macflipliquid2.cpp)
add_library(macflipliquid3 STATIC ${headers} macflipliquid3.cpp)

target_link_libraries(macliquid2 core)
target_link_libraries(macliquid3 core)
target_link_libraries(macflipliquid2 macliquid2)
target_link_libraries(macflipliquid3 macliquid3)

target_compile_definitions(macliquid2 PRIVATE "SPATIAL_DIM=2")
target_compile_definitions(macliquid3 PRIVATE "SPATIAL_DIM=3")
target_compile_definitions(macflipliquid2 PRIVATE "SPATIAL_DIM=2")
target_compile_definitions(macflipliquid3 PRIVATE "SPATIAL_DIM=3")
