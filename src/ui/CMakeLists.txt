add_library(ui STATIC ${headers} ui.cpp graphics_gl.cpp)
add_library(camera2 STATIC ${headers} camera2.cpp)
add_library(camera3 STATIC ${headers} camera3.cpp)

target_link_libraries(ui core ${Boost_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} glfw)
target_link_libraries(camera2 core)
target_link_libraries(camera3 core)

target_compile_definitions(ui PRIVATE "SPATIAL_DIM=2")
target_compile_definitions(camera2 PRIVATE "SPATIAL_DIM=2")
target_compile_definitions(camera3 PRIVATE "SPATIAL_DIM=3")
