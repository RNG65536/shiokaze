cmake_minimum_required(VERSION 3.12)
project(shiokaze_sim)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

add_compile_definitions("BOOST_ALL_DYN_LINK" "__TBB_NO_IMPLICIT_LINKAGE")

add_compile_definitions("SHKZ_DEBUG=1" "SHKZ_SUFFIX=\"_debug\"" "NUM_THREAD=8" "USE_OPENGL=1" "BOOST_ALL_DYN_LINK" "__TBB_NO_IMPLICIT_LINKAGE")

#add_compile_options("-std=c++14")

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glew REQUIRED)
find_package(GLUT REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem system date_time)
find_package(gsl REQUIRED)
find_package(zlib REQUIRED)
find_package(TBB REQUIRED)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/local/include
    ${Boost_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIR}
    ${GSL_INCLUDE_DIRS}
    ${ZLIB_INCLUDE_DIRS}
    ${Tbb_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIR}
    )

file(GLOB_RECURSE headers "include/*.h")


#core
add_library(core SHARED ${headers}
src/core/configurable.cpp
src/core/configuration.cpp
src/core/console.cpp
src/core/deadline.cpp
src/core/dylibloader.cpp
src/core/filesystem.cpp
src/core/global_timer.cpp
src/core/module.cpp
src/core/scoped_timer.cpp
src/core/shared_array_core2.cpp
src/core/shared_array_core3.cpp
src/dlfcn.c
)
target_compile_definitions(core PRIVATE "DLLEXPORT_CORE" "DLFCN_WIN32_EXPORTS")
target_link_libraries(core ${Boost_LIBRARIES})

#advection
add_library(macadvection2 SHARED ${headers} src/advection/macadvection2.cpp)
add_library(macadvection3 SHARED ${headers} src/advection/macadvection3.cpp)
target_compile_definitions(macadvection2 PRIVATE "DLLEXPORT_MACADVECTION2" "SPATIAL_DIM=2")
target_compile_definitions(macadvection3 PRIVATE "DLLEXPORT_MACADVECTION3" "SPATIAL_DIM=3")
target_link_libraries(macadvection2 core)
target_link_libraries(macadvection3 core)

#array
add_library(bitcount SHARED ${headers} src/array/bitcount/bitcount.cpp)
add_library(lineararray2 SHARED ${headers} src/array/lineararray2.cpp)
add_library(lineararray3 SHARED ${headers} src/array/lineararray3.cpp)
add_library(tiledarray2 SHARED ${headers} src/array/tiledarray2.cpp)
add_library(tiledarray3 SHARED ${headers} src/array/tiledarray3.cpp)
add_library(treearray2 SHARED ${headers} src/array/treearray2.cpp)
add_library(treearray3 SHARED ${headers} src/array/treearray3.cpp)
target_compile_definitions(bitcount PRIVATE "DLLEXPORT_BITCOUNT")
target_compile_definitions(lineararray2 PRIVATE "DLLEXPORT_LINEARARRAY2" "SPATIAL_DIM=2")
target_compile_definitions(lineararray3 PRIVATE "DLLEXPORT_LINEARARRAY3" "SPATIAL_DIM=3")
target_compile_definitions(tiledarray2 PRIVATE "DLLEXPORT_TILEDARRAY2" "SPATIAL_DIM=2")
target_compile_definitions(tiledarray3 PRIVATE "DLLEXPORT_TILEDARRAY3" "SPATIAL_DIM=3")
target_compile_definitions(treearray2 PRIVATE "DLLEXPORT_TREEARRAY2" "SPATIAL_DIM=2")
target_compile_definitions(treearray3 PRIVATE "DLLEXPORT_TREEARRAY3" "SPATIAL_DIM=3")
target_link_libraries(bitcount core)
target_link_libraries(lineararray2 core bitcount)
target_link_libraries(lineararray3 core bitcount)
target_link_libraries(tiledarray2 core bitcount)
target_link_libraries(tiledarray3 core bitcount)
target_link_libraries(treearray2 core bitcount)
target_link_libraries(treearray3 core bitcount)

#backwardflip
add_library(macbackwardflip2 SHARED ${headers} src/backwardflip/macbackwardflip2.cpp)
add_library(macbackwardflip3 SHARED ${headers} src/backwardflip/macbackwardflip3.cpp)
target_compile_definitions(macbackwardflip2 PRIVATE "DLLEXPORT_MACBACKWARDFLIP2" "SPATIAL_DIM=2")
target_compile_definitions(macbackwardflip3 PRIVATE "DLLEXPORT_MACBACKWARDFLIP3" "SPATIAL_DIM=3")
target_link_libraries(macbackwardflip2 core)
target_link_libraries(macbackwardflip3 core)

#cellmesher
add_library(marchingcubes SHARED ${headers} src/cellmesher/marchingcubes.cpp)
add_library(dualmc SHARED ${headers} src/cellmesher/dualmc.cpp)
target_compile_definitions(marchingcubes PRIVATE "DLLEXPORT_MARCHINGCUBES")
target_compile_definitions(dualmc PRIVATE "DLLEXPORT_DUALMC")
target_link_libraries(marchingcubes core)
target_link_libraries(dualmc core)

#flip
add_library(macnbflip2 SHARED ${headers} src/flip/macnbflip2.cpp)
add_library(macnbflip3 SHARED ${headers} src/flip/macnbflip3.cpp)
add_library(macexnbflip2 SHARED ${headers} src/flip/macexnbflip2.cpp)
add_library(macexnbflip3 SHARED ${headers} src/flip/macexnbflip3.cpp)
target_compile_definitions(macnbflip2 PRIVATE "DLLEXPORT_MACNBFLIP2" "SPATIAL_DIM=2")
target_compile_definitions(macnbflip3 PRIVATE "DLLEXPORT_MACNBFLIP3" "SPATIAL_DIM=3")
target_compile_definitions(macexnbflip2 PRIVATE "DLLEXPORT_MACEXNBFLIP2" "SPATIAL_DIM=2")
target_compile_definitions(macexnbflip3 PRIVATE "DLLEXPORT_MACEXNBFLIP3" "SPATIAL_DIM=3")
target_link_libraries(macnbflip2 core)
target_link_libraries(macnbflip3 core)
target_link_libraries(macexnbflip2 core macnbflip2)
target_link_libraries(macexnbflip3 core macnbflip3)

#images
add_library(image_io SHARED ${headers} src/images/image_io.cpp src/images/lodepng/lodepng.cpp)
target_compile_definitions(image_io PRIVATE "DLLEXPORT_IMAGEIO")
target_link_libraries(image_io core)

#linsolver
add_library(cg SHARED ${headers} src/linsolver/cg.cpp)
add_library(pcg SHARED ${headers} src/linsolver/pcg.cpp)
add_library(amg SHARED ${headers} src/linsolver/amg.cpp)
target_compile_definitions(cg PRIVATE "DLLEXPORT_CG" "INDEX_TYPE=size_t" "FLOAT_TYPE=double")
target_compile_definitions(pcg PRIVATE "DLLEXPORT_PCG" "INDEX_TYPE=size_t" "FLOAT_TYPE=double")
target_compile_definitions(amg PRIVATE "DLLEXPORT_AMG" "INDEX_TYPE=size_t" "FLOAT_TYPE=double")
target_link_libraries(cg core)
target_link_libraries(pcg core ${GSL_LIBRARIES})
target_link_libraries(amg core)

#liquid
add_library(macliquid2 SHARED ${headers} src/liquid/macliquid2.cpp)
add_library(macliquid3 SHARED ${headers} src/liquid/macliquid3.cpp)
add_library(macflipliquid2 SHARED ${headers} src/liquid/macflipliquid2.cpp)
add_library(macflipliquid3 SHARED ${headers} src/liquid/macflipliquid3.cpp)
target_compile_definitions(macliquid2 PRIVATE "DLLEXPORT_MACLIQUID2" "SPATIAL_DIM=2")
target_compile_definitions(macliquid3 PRIVATE "DLLEXPORT_MACLIQUID3" "SPATIAL_DIM=3")
target_compile_definitions(macflipliquid2 PRIVATE "DLLEXPORT_MACFLIPLIQUID2" "SPATIAL_DIM=2")
target_compile_definitions(macflipliquid3 PRIVATE "DLLEXPORT_MACFLIPLIQUID3" "SPATIAL_DIM=3")
target_link_libraries(macliquid2 core)
target_link_libraries(macliquid3 core)
target_link_libraries(macflipliquid2 core macliquid2)
target_link_libraries(macflipliquid3 core macliquid3)

#math
add_library(RCMatrix SHARED ${headers} src/math/RCMatrix.cpp)
target_compile_definitions(RCMatrix PRIVATE "DLLEXPORT_RCMATRIX" "INDEX_TYPE=size_t" "FLOAT_TYPE=double")
target_link_libraries(RCMatrix core ${GSL_LIBRARIES})

#meshexporter
add_library(meshexporter3 SHARED ${headers} src/meshexporter/meshexporter3.cpp)
target_compile_definitions(meshexporter3 PRIVATE "DLLEXPORT_MESHEXPORTER")
target_link_libraries(meshexporter3 core ${ZLIB_LIBRARIES})

#ordering
add_library(lineordering SHARED ${headers} src/ordering/lineordering.cpp)
add_library(blockordering SHARED ${headers} src/ordering/blockordering.cpp)
add_library(zordering SHARED ${headers} src/ordering/zordering.cpp)
target_compile_definitions(lineordering PRIVATE "DLLEXPORT_LINEORDERING")
target_compile_definitions(blockordering PRIVATE "DLLEXPORT_BLOCKORDERING")
target_compile_definitions(zordering PRIVATE "DLLEXPORT_ZORDERING")
target_link_libraries(lineordering core)
target_link_libraries(blockordering core)
target_link_libraries(zordering core)

#parallel
add_library(stdthread SHARED ${headers} src/parallel/stdthread.cpp)
add_library(tbbthread SHARED ${headers} src/parallel/tbbthread.cpp)
add_library(sequential_splitter SHARED ${headers} src/parallel/sequential_splitter.cpp)
add_library(dispersed_splitter SHARED ${headers} src/parallel/dispersed_splitter.cpp)
target_compile_definitions(stdthread PRIVATE "DLLEXPORT_STDTHREAD")
target_compile_definitions(tbbthread PRIVATE "DLLEXPORT_TBBTHREAD")
target_compile_definitions(sequential_splitter PRIVATE "DLLEXPORT_SEQUENTIALSPLITTER")
target_compile_definitions(dispersed_splitter PRIVATE "DLLEXPORT_DISPERSEDSPLITTER")
target_link_libraries(stdthread core)
target_link_libraries(tbbthread ${Tbb_LIBRARIES} core)
target_link_libraries(sequential_splitter core)
target_link_libraries(dispersed_splitter core)

#particlerasterizer
add_library(flatrasterizer2 SHARED ${headers} src/particlerasterizer/flatrasterizer2.cpp)
add_library(flatrasterizer3 SHARED ${headers} src/particlerasterizer/flatrasterizer3.cpp)
add_library(convexhullrasterizer2 SHARED ${headers} src/particlerasterizer/convexhullrasterizer2.cpp)
add_library(convexhullrasterizer3 SHARED ${headers} src/particlerasterizer/convexhullrasterizer3.cpp)
target_compile_definitions(flatrasterizer2 PRIVATE "DLLEXPORT_FLATRASTERIZER2" "SPATIAL_DIM=2")
target_compile_definitions(flatrasterizer3 PRIVATE "DLLEXPORT_FLATRASTERIZER3" "SPATIAL_DIM=3")
target_compile_definitions(convexhullrasterizer2 PRIVATE "DLLEXPORT_CONVEXHULLRASTERIZER2" "SPATIAL_DIM=2")
target_compile_definitions(convexhullrasterizer3 PRIVATE "DLLEXPORT_CONVEXHULLRASTERIZER3" "SPATIAL_DIM=3")
target_link_libraries(flatrasterizer2 core)
target_link_libraries(flatrasterizer3 core)
target_link_libraries(convexhullrasterizer2 core)
target_link_libraries(convexhullrasterizer3 core)

#pointgridhash
add_library(pointgridhash2 SHARED ${headers} src/pointgridhash/pointgridhash2.cpp)
add_library(pointgridhash3 SHARED ${headers} src/pointgridhash/pointgridhash3.cpp)
target_compile_definitions(pointgridhash2 PRIVATE "DLLEXPORT_POINTGRIDHASH2" "SPATIAL_DIM=2")
target_compile_definitions(pointgridhash3 PRIVATE "DLLEXPORT_POINTGRIDHASH3" "SPATIAL_DIM=3")
target_link_libraries(pointgridhash2 core)
target_link_libraries(pointgridhash3 core)

#polygon
add_library(polygon3 SHARED ${headers} src/polygon/polygon3.cpp src/polygon/rply/rply.c)
target_compile_definitions(polygon3 PRIVATE "DLLEXPORT_POLYGON3" "SPATIAL_DIM=3")
target_link_libraries(polygon3 core)
#target_link_libraries(polygon3 levelset3)

#projection
add_library(macpressuresolver2 SHARED ${headers} src/projection/macpressuresolver2.cpp)
add_library(macpressuresolver3 SHARED ${headers} src/projection/macpressuresolver3.cpp)
add_library(macstreamfuncsolver2 SHARED ${headers} src/projection/macstreamfuncsolver2.cpp)
add_library(macstreamfuncsolver3 SHARED ${headers} src/projection/macstreamfuncsolver3.cpp)
target_compile_definitions(macpressuresolver2 PRIVATE "DLLEXPORT_MACPRESSURESOLVER2" "SPATIAL_DIM=2")
target_compile_definitions(macpressuresolver3 PRIVATE "DLLEXPORT_MACPRESSURESOLVER3" "SPATIAL_DIM=3")
target_compile_definitions(macstreamfuncsolver2 PRIVATE "DLLEXPORT_MACSTREAMFUNCSOLVER2" "SPATIAL_DIM=2")
target_compile_definitions(macstreamfuncsolver3 PRIVATE "DLLEXPORT_MACSTREAMFUNCSOLVER3" "SPATIAL_DIM=3")
target_link_libraries(macpressuresolver2 core)
target_link_libraries(macpressuresolver3 core)
target_link_libraries(macstreamfuncsolver2 core)
target_link_libraries(macstreamfuncsolver3 core)

#redistancer
add_library(pderedistancer2 SHARED ${headers} src/redistancer/pderedistancer2.cpp)
add_library(pderedistancer3 SHARED ${headers} src/redistancer/pderedistancer3.cpp)
add_library(fastmarch2 SHARED ${headers} src/redistancer/fastmarch2.cpp)
add_library(fastmarch3 SHARED ${headers} src/redistancer/fastmarch3.cpp)
target_compile_definitions(pderedistancer2 PRIVATE "DLLEXPORT_PDEREDISTANCER2" "SPATIAL_DIM=2")
target_compile_definitions(pderedistancer3 PRIVATE "DLLEXPORT_PDEREDISTANCER3" "SPATIAL_DIM=3")
target_compile_definitions(fastmarch2 PRIVATE "DLLEXPORT_FASTMARCH2" "SPATIAL_DIM=2")
target_compile_definitions(fastmarch3 PRIVATE "DLLEXPORT_FASTMARCH3" "SPATIAL_DIM=3")
target_link_libraries(pderedistancer2 core)
target_link_libraries(pderedistancer3 core)
target_link_libraries(fastmarch2 core)
target_link_libraries(fastmarch3 core)

#rigidbody
#######################################################

#SDFGen
add_library(SDFGen SHARED ${headers} src/SDFGen/SDFGen.cpp src/SDFGen/makelevelset3.cpp)
target_compile_definitions(SDFGen PRIVATE "DLLEXPORT_SDFGEN" "SPATIAL_DIM=3")
target_link_libraries(SDFGen core)

#timestepper
add_library(timestepper SHARED ${headers} src/timestepper/timestepper.cpp)
target_compile_definitions(timestepper PRIVATE "DLLEXPORT_TIMESTEPPER")
target_link_libraries(timestepper core)

#utility
add_library(gridutility2 SHARED ${headers} src/utility/gridutility2.cpp)
add_library(gridutility3 SHARED ${headers} src/utility/gridutility3.cpp)
add_library(macutility2 SHARED ${headers} src/utility/macutility2.cpp)
add_library(macutility3 SHARED ${headers} src/utility/macutility3.cpp)
add_library(macstats2 SHARED ${headers} src/utility/macstats2.cpp)
add_library(macstats3 SHARED ${headers} src/utility/macstats3.cpp)
add_library(meshutility2 SHARED ${headers} src/utility/meshutility2.cpp)
add_library(meshutility3 SHARED ${headers} src/utility/meshutility3.cpp)
target_compile_definitions(gridutility2 PRIVATE "DLLEXPORT_GRIDUTILITY2" "SPATIAL_DIM=2")
target_compile_definitions(gridutility3 PRIVATE "DLLEXPORT_GRIDUTILITY3" "SPATIAL_DIM=3")
target_compile_definitions(macutility2 PRIVATE "DLLEXPORT_MACUTILITY2" "SPATIAL_DIM=2")
target_compile_definitions(macutility3 PRIVATE "DLLEXPORT_MACUTILITY3" "SPATIAL_DIM=3")
target_compile_definitions(macstats2 PRIVATE "DLLEXPORT_MACSTATS2" "SPATIAL_DIM=2")
target_compile_definitions(macstats3 PRIVATE "DLLEXPORT_MACSTATS3" "SPATIAL_DIM=3")
target_compile_definitions(meshutility2 PRIVATE "DLLEXPORT_MESHUTILITY2" "SPATIAL_DIM=2")
target_compile_definitions(meshutility3 PRIVATE "DLLEXPORT_MESHUTILITY3" "SPATIAL_DIM=3")
target_link_libraries(gridutility2 core)
target_link_libraries(gridutility3 core)
target_link_libraries(macutility2 core)
target_link_libraries(macutility3 core)
target_link_libraries(macstats2 core)
target_link_libraries(macstats3 core)
target_link_libraries(meshutility2 core)
target_link_libraries(meshutility3 core)

#smoke
add_library(macsmoke2 SHARED ${headers} src/smoke/macsmoke2.cpp)
add_library(macsmoke3 SHARED ${headers} src/smoke/macsmoke3.cpp)
add_library(macflipsmoke2 SHARED ${headers} src/smoke/macflipsmoke2.cpp)
add_library(macflipsmoke3 SHARED ${headers} src/smoke/macflipsmoke3.cpp)
add_library(macbackwardflipsmoke2 SHARED ${headers} src/smoke/macbackwardflipsmoke2.cpp)
add_library(macbackwardflipsmoke3 SHARED ${headers} src/smoke/macbackwardflipsmoke3.cpp)
target_compile_definitions(macsmoke2 PRIVATE "DLLEXPORT_MACSMOKE2" "SPATIAL_DIM=2")
target_compile_definitions(macsmoke3 PRIVATE "DLLEXPORT_MACSMOKE3" "SPATIAL_DIM=3")
target_compile_definitions(macflipsmoke2 PRIVATE "DLLEXPORT_MACFLIPSMOKE2" "SPATIAL_DIM=2")
target_compile_definitions(macflipsmoke3 PRIVATE "DLLEXPORT_MACFLIPSMOKE3" "SPATIAL_DIM=3")
target_compile_definitions(macbackwardflipsmoke2 PRIVATE "DLLEXPORT_MACBACKWARDFLIPSMOKE2" "SPATIAL_DIM=2")
target_compile_definitions(macbackwardflipsmoke3 PRIVATE "DLLEXPORT_MACBACKWARDFLIPSMOKE3" "SPATIAL_DIM=3")
target_link_libraries(macsmoke2 core timestepper macutility2 image_io)
target_link_libraries(macsmoke3 core timestepper macutility3 image_io)
target_link_libraries(macflipsmoke2 macsmoke2)
target_link_libraries(macflipsmoke3 macsmoke3)
target_link_libraries(macbackwardflipsmoke2 macsmoke2)
target_link_libraries(macbackwardflipsmoke3 macsmoke3)

#surfacetracker
add_library(maclevelsetsurfacetracker2 SHARED ${headers} src/surfacetracker/maclevelsetsurfacetracker2.cpp)
add_library(maclevelsetsurfacetracker3 SHARED ${headers} src/surfacetracker/maclevelsetsurfacetracker3.cpp)
target_compile_definitions(maclevelsetsurfacetracker2 PRIVATE "DLLEXPORT_MACLEVELSETSURFACETRACKER2" "SPATIAL_DIM=2")
target_compile_definitions(maclevelsetsurfacetracker3 PRIVATE "DLLEXPORT_MACLEVELSETSURFACETRACKER3" "SPATIAL_DIM=3")
target_link_libraries(maclevelsetsurfacetracker2 core)
target_link_libraries(maclevelsetsurfacetracker3 core)

#system
add_library(environment SHARED ${headers} src/system/environment.cpp)
add_library(sysstats SHARED ${headers} src/system/sysstats.cpp)
target_compile_definitions(environment PRIVATE "DLLEXPORT_ENVIRONMENT")
target_compile_definitions(sysstats PRIVATE "DLLEXPORT_SYSSTATS")
target_link_libraries(environment core)
target_link_libraries(sysstats core)

#ui
add_library(ui SHARED ${headers} src/ui/ui.cpp src/ui/graphics_gl.cpp)
add_library(camera2 SHARED ${headers} src/ui/camera2.cpp)
add_library(camera3 SHARED ${headers} src/ui/camera3.cpp)
target_compile_definitions(ui PRIVATE "DLLEXPORT_UI" "SPATIAL_DIM=2")
target_compile_definitions(camera2 PRIVATE "DLLEXPORT_CAMERA2" "SPATIAL_DIM=2")
target_compile_definitions(camera3 PRIVATE "DLLEXPORT_CAMERA3" "SPATIAL_DIM=3")
target_link_libraries(ui ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLUT_LIBRARIES} glfw core)
target_link_libraries(camera2 core)
target_link_libraries(camera3 core)

#visualizer
add_library(gridvisualizer2 SHARED ${headers} src/visualizer/gridvisualizer2.cpp)
add_library(gridvisualizer3 SHARED ${headers} src/visualizer/gridvisualizer3.cpp)
add_library(macvisualizer2 SHARED ${headers} src/visualizer/macvisualizer2.cpp)
add_library(macvisualizer3 SHARED ${headers} src/visualizer/macvisualizer3.cpp)
target_compile_definitions(gridvisualizer2 PRIVATE "DLLEXPORT_GRIDVISUALIZER2" "SPATIAL_DIM=2")
target_compile_definitions(gridvisualizer3 PRIVATE "DLLEXPORT_GRIDVISUALIZER3" "SPATIAL_DIM=3")
target_compile_definitions(macvisualizer2 PRIVATE "DLLEXPORT_MACVISUALIZER2" "SPATIAL_DIM=2")
target_compile_definitions(macvisualizer3 PRIVATE "DLLEXPORT_MACVISUALIZER3" "SPATIAL_DIM=3")
target_link_libraries(gridvisualizer2 core)
target_link_libraries(gridvisualizer3 core)
target_link_libraries(macvisualizer2 core)
target_link_libraries(macvisualizer3 core)

#examples
add_library(arraybenchmark2-example SHARED ${headers} src/examples/arraybenchmark2-example.cpp)
add_library(arraybenchmark3-example SHARED ${headers} src/examples/arraybenchmark3-example.cpp)
add_library(demo-example SHARED ${headers} src/examples/demo-example.cpp)
add_library(dilation2-example SHARED ${headers} src/examples/dilation2-example.cpp)
add_library(dilation3-example SHARED ${headers} src/examples/dilation3-example.cpp)
add_library(gridops3-example SHARED ${headers} src/examples/gridops3-example.cpp)
add_library(levelset2-example SHARED ${headers} src/examples/levelset2-example.cpp)
add_library(levelset3-example SHARED ${headers} src/examples/levelset3-example.cpp)
add_library(meshexporter3-demo SHARED ${headers} src/examples/meshexporter-demo3.cpp)
add_library(rigidbody2-example SHARED ${headers} src/examples/rigidbody2-example.cpp)
add_library(rigidbody3-example SHARED ${headers} src/examples/rigidbody3-example.cpp)
add_library(treearray2-example SHARED ${headers} src/examples/treearray2-example.cpp)
add_library(treearray3-example SHARED ${headers} src/examples/treearray3-example.cpp)
target_compile_definitions(arraybenchmark2-example PRIVATE "DLLEXPORT_ARRAYBENCHMARK2EXAMPLE" "SPATIAL_DIM=2")
target_compile_definitions(arraybenchmark3-example PRIVATE "DLLEXPORT_ARRAYBENCHMARK3EXAMPLE" "SPATIAL_DIM=3")
target_compile_definitions(demo-example PRIVATE "DLLEXPORT_DEMOEXAMPLE" "SPATIAL_DIM=2")
target_compile_definitions(dilation2-example PRIVATE "DLLEXPORT_DILATION2EXAMPLE" "SPATIAL_DIM=2")
target_compile_definitions(dilation3-example PRIVATE "DLLEXPORT_DILATION3EXAMPLE" "SPATIAL_DIM=3")
target_compile_definitions(gridops3-example PRIVATE "DLLEXPORT_GRIDOPS3EXAMPLE" "SPATIAL_DIM=3")
target_compile_definitions(levelset2-example PRIVATE "DLLEXPORT_LEVELSET2EXAMPLE" "SPATIAL_DIM=2")
target_compile_definitions(levelset3-example PRIVATE "DLLEXPORT_LEVELSET3EXAMPLE" "SPATIAL_DIM=3")
target_compile_definitions(meshexporter3-demo PRIVATE "DLLEXPORT_MESHEXPORTER3DEMO" "SPATIAL_DIM=3")
target_compile_definitions(rigidbody2-example PRIVATE "DLLEXPORT_RIGIDBODY2EXAMPLE" "SPATIAL_DIM=2")
target_compile_definitions(rigidbody3-example PRIVATE "DLLEXPORT_RIGIDBODY3EXAMPLE" "SPATIAL_DIM=3")
target_compile_definitions(treearray2-example PRIVATE "DLLEXPORT_TREEARRAY2EXAMPLE" "SPATIAL_DIM=2")
target_compile_definitions(treearray3-example PRIVATE "DLLEXPORT_TREEARRAY3EXAMPLE" "SPATIAL_DIM=3")
target_link_libraries(arraybenchmark2-example core)
target_link_libraries(arraybenchmark3-example core)
target_link_libraries(demo-example core)
target_link_libraries(dilation2-example core)
target_link_libraries(dilation3-example core)
target_link_libraries(gridops3-example core)
target_link_libraries(levelset2-example core)
target_link_libraries(levelset3-example core)
target_link_libraries(meshexporter3-demo core)
target_link_libraries(rigidbody2-example core)
target_link_libraries(rigidbody3-example core)
target_link_libraries(treearray2-example core)
target_link_libraries(treearray3-example core)

#resources
add_library(dambreak2 SHARED ${headers} resources/liquid/dambreak2.cpp)
target_compile_definitions(dambreak2 PRIVATE "DLLEXPORT_DAMBREAK2" "SPATIAL_DIM=2")
target_link_libraries(dambreak2 core)


add_executable(launcher launcher/src/main.cpp)
target_link_libraries(launcher core)
