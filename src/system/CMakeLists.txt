add_library(environment STATIC ${headers} environment.cpp)
add_library(sysstats STATIC ${headers} sysstats.cpp)

target_link_libraries(environment core ${Boost_LIBRARIES})
target_link_libraries(sysstats core)
