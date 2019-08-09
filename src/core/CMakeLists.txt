add_library(core STATIC ${headers}
configurable.cpp
configuration.cpp
console.cpp
deadline.cpp
dylibloader.cpp
filesystem.cpp
global_timer.cpp
module.cpp
scoped_timer.cpp
shared_array_core2.cpp
shared_array_core3.cpp
../dlfcn.c
)

target_link_libraries(core ${Boost_LIBRARIES})
