add_library(image_io STATIC ${headers} image_io.cpp lodepng/lodepng.cpp)

target_link_libraries(image_io core)
