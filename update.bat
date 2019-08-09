cd _build
cmake .. -G "Visual Studio 15 Win64" -Dglfw3_DIR="C:/Deps/glfw/lib/cmake/glfw3" -DBOOST_ROOT="C:/Deps/boost" -DGLEW_ROOT_PATH="C:/Deps/glew" -DGSL_ROOT_DIR="C:/Deps/gsl" -DZLIB_ROOT="C:/Deps/zlib" -DTBB_ROOT="C:/Deps/tbb" -DGLUT_ROOT_PATH="C:/Deps/freeglut"
cd ..