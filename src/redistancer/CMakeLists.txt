add_library(pderedistancer2 STATIC ${headers} pderedistancer2.cpp)
add_library(pderedistancer3 STATIC ${headers} pderedistancer3.cpp)
add_library(fastmarch2 STATIC ${headers} fastmarch2.cpp)
add_library(fastmarch3 STATIC ${headers} fastmarch3.cpp)

target_link_libraries(pderedistancer2 core)
target_link_libraries(pderedistancer3 core)
target_link_libraries(fastmarch2 core)
target_link_libraries(fastmarch3 core)

target_compile_definitions(pderedistancer2 PRIVATE "SPATIAL_DIM=2")
target_compile_definitions(pderedistancer3 PRIVATE "SPATIAL_DIM=3")
target_compile_definitions(fastmarch2 PRIVATE "SPATIAL_DIM=2")
target_compile_definitions(fastmarch3 PRIVATE "SPATIAL_DIM=3")
