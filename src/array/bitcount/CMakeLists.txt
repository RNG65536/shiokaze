add_library(bitcount STATIC ${headers} bitcount.cpp)

target_link_libraries(bitcount core)
