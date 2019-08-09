/*
**	main.cpp
**
**	This is part of Shiokaze, a research-oriented fluid solver for computer graphics.
**	Created by Ryoichi Ando <rand@nii.ac.jp> on Feb 25, 2018.
**
**	Permission is hereby granted, free of charge, to any person obtaining a copy of
**	this software and associated documentation files (the "Software"), to deal in
**	the Software without restriction, including without limitation the rights to use,
**	copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
**	Software, and to permit persons to whom the Software is furnished to do so,
**	subject to the following conditions:
**
**	The above copyright notice and this permission notice shall be included in all copies
**	or substantial portions of the Software.
**
**	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
**	INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
**	PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
**	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
**	CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
**	OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
//
#include <iostream>
#include <dlfcn.h>
#include <thread>
#include <mutex>
#include <shiokaze/core/filesystem.h>

#include <ui/ui.h>
//
SHKZ_USING_NAMESPACE
//
// NOTE : to specify an example, pass Target=${DemoName} as arguments
int main ( int argc, const char* argv[] ) {
	//
	//pthread_mutex_t mutex;
	//pthread_mutex_init(&mutex, NULL);
    std::mutex mutex;
    
    //
	std::thread dummy([](){}); dummy.join(); // Dummy code to enforce linking against thread
	//const auto handle = ::dlopen(filesystem::resolve_libname("shiokaze_ui").c_str(),RTLD_LAZY);
	const auto handle = ::dlopen(filesystem::resolve_libname("ui").c_str(),RTLD_LAZY);
	int result (0);
	if( ! handle ) {
		std::cout << "Could not open the library: " << ::dlerror() << std::endl;
	} else {
		const auto run_func = ::dlsym(handle,"run");
		if( ! run_func ) {
			std::cout << "Could not load the function: " << ::dlerror() << std::endl;
		} else {
			const auto func = reinterpret_cast<int(*)(int argc, const char* argv[])>(run_func);
			result = func(argc,argv);
			if(::dlclose(handle)) {
				std::cout << "Could not close the handle: " << ::dlerror() << std::endl;
			}
		}
	}
	return result;
//
}
//