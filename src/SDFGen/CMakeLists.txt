add_library(SDFGen STATIC ${headers} SDFGen.cpp makelevelset3.cpp)

target_link_libraries(SDFGen core)

target_compile_definitions(SDFGen PRIVATE "SPATIAL_DIM=3")
