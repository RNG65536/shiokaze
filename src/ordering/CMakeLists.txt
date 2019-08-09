add_library(lineordering STATIC ${headers} lineordering.cpp)
add_library(blockordering STATIC ${headers} blockordering.cpp)
add_library(zordering STATIC ${headers} zordering.cpp)

target_link_libraries(lineordering core)
target_link_libraries(blockordering core)
target_link_libraries(zordering core)
