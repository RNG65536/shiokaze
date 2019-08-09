add_library(polygon3 STATIC ${headers} polygon3.cpp rply/rply.c)

target_link_libraries(polygon3 core levelset3)

target_compile_definitions(polygon3 PRIVATE "SPATIAL_DIM=3")
