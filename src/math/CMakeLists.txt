add_library(RCMatrix STATIC ${headers} RCMatrix.cpp)

target_link_libraries(RCMatrix core gsl)

target_compile_definitions(RCMatrix PRIVATE "INDEX_TYPE=size_t" "FLOAT_TYPE=double")
