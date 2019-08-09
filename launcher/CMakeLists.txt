add_executable(launcher ${headers} src/main.cpp)

target_link_libraries(launcher core ui)