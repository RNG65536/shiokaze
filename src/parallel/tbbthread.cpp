/*
**	stdthread.cpp
**
**	This is part of Shiokaze, a research-oriented fluid solver for computer graphics.
**	Created by Ryoichi Ando <rand@nii.ac.jp> on Feb 1, 2017. 
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
#ifndef SHKZ_TBBTHREAD_H
#define SHKZ_TBBTHREAD_H
#define TBB_PREVIEW_GLOBAL_CONTROL 1
//
#include <shiokaze/parallel/parallel_core.h>
#include <cmath>
#include <tbb/tbb.h>
//
SHKZ_BEGIN_NAMESPACE
//
class tbbthread : public parallel_core {
protected:
	//
	LONG_NAME("TBB Thread")
	MODULE_NAME("tbbthread")
	//
	virtual void for_each(
		std::function<void(size_t n, int thread_index)> func,
		std::function<size_t(int thread_index)> iterator_start,
		std::function<bool(size_t &n, int thread_index)> iterator_advance,
		int num_threads ) const override {
		//
		assert( num_threads );
		std::vector<tbb::tbb_thread> threads(num_threads);
		for( int q=0; q<num_threads; ++q ) {
			threads[q] = tbb::tbb_thread([&]( int q ){
				size_t n = iterator_start(q);
				do { func(n,q); } while( iterator_advance(n,q));
			},q);
		}
		for( auto& thread : threads ) thread.join();
	}
	//
	virtual void run( const std::vector<std::function<void()> > &functions ) const override {
		std::vector<tbb::tbb_thread> threads(functions.size());
		for( int q=0; q<threads.size(); ++q ) {
			threads[q] = tbb::tbb_thread([&](int q) { functions[q](); },q);
		}
		for( auto& thread : threads ) thread.join();
	}
	//
};
//
#ifdef DLLEXPORT_TBBTHREAD
#define DLLAPI_TBBTHREAD DLLAPI_EXPORT
#else
#define DLLAPI_TBBTHREAD DLLAPI_IMPORT
#endif

extern "C" DLLAPI_TBBTHREAD module * create_instance() {
	return new tbbthread();
}
//
extern "C" const char *license() {
	return "MIT";
}
//
SHKZ_END_NAMESPACE
//
#endif
//