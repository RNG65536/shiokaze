add_library(maclevelsetsurfacetracker2 STATIC ${headers} maclevelsetsurfacetracker2.cpp)
add_library(maclevelsetsurfacetracker3 STATIC ${headers} maclevelsetsurfacetracker3.cpp)

target_link_libraries(maclevelsetsurfacetracker2 core)
target_link_libraries(maclevelsetsurfacetracker3 core)

target_compile_definitions(maclevelsetsurfacetracker2 PRIVATE "SPATIAL_DIM=2")
target_compile_definitions(maclevelsetsurfacetracker3 PRIVATE "SPATIAL_DIM=3")
