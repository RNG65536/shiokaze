add_library(cg STATIC ${headers} cg.cpp)
add_library(pcg STATIC ${headers} pcg.cpp)
add_library(amg STATIC ${headers} amg.cpp)

target_link_libraries(cg core)
target_link_libraries(pcg core gsl)
target_link_libraries(amg core)

target_compile_definitions(cg PRIVATE "INDEX_TYPE=size_t" "FLOAT_TYPE=double")
target_compile_definitions(pcg PRIVATE "INDEX_TYPE=size_t" "FLOAT_TYPE=double")
target_compile_definitions(amg PRIVATE "INDEX_TYPE=size_t" "FLOAT_TYPE=double")
