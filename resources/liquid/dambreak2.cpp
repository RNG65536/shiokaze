/*
**	dambreak2.cpp
**
**	This is part of Shiokaze, a research-oriented fluid solver for computer graphics.
**	Created by Ryoichi Ando <rand@nii.ac.jp> on June 20, 2017. 
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
#include <shiokaze/math/vec.h>
#include <shiokaze/core/configuration.h>
#include <string>
#include <cmath>
#include <algorithm>
//
SHKZ_USING_NAMESPACE
//

#ifdef DLLEXPORT_DAMBREAK2
#define DLLAPI_DAMBREAK2 DLLAPI_EXPORT
#else
#define DLLAPI_DAMBREAK2 DLLAPI_IMPORT
#endif

static double width (0.232), height (0.432), level (0.095), depth (0.2532);
//
extern "C" DLLAPI_DAMBREAK2 void configure( configuration &config ) {
	configuration::auto_group group(config,"Dambreak Scene 3D","Dambreak");
	config.get_double("Width",width,"Width of the dam");
	config.get_double("Height",height,"Height of the dam");
	config.get_double("Level",level,"Height of the pool");
}
//
extern "C" DLLAPI_DAMBREAK2 double fluid( const vec3d &p ) {
	double value = -1e9;
	value = std::max(value,p[0]-width);
	value = std::max(value,p[1]-height);
	value = std::min(value,p[1]-level);
	return value;
}
//
extern "C" DLLAPI_DAMBREAK2 const char *license() {
	return "MIT";
}