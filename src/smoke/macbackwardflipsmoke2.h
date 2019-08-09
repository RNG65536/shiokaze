/*
**	macbackwardflipsmoke2.h
**
**	This is part of Shiokaze, a research-oriented fluid solver for computer graphics.
**	Created by Ryoichi Ando <rand@nii.ac.jp> on June 8, 2017. 
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
#ifndef SHKZ_BACKWARDFLIPSMOKE2_H
#define SHKZ_BACKWARDFLIPSMOKE2_H
//
#include "macsmoke2.h"
#include <shiokaze/backwardflip/macbackwardflip2_interface.h>
//
SHKZ_BEGIN_NAMESPACE
//

#ifdef DLLEXPORT_MACBACKWARDFLIPSMOKE2
#define DLLAPI_MACBACKWARDFLIPSMOKE2 DLLAPI_EXPORT
#else
#define DLLAPI_MACBACKWARDFLIPSMOKE2 DLLAPI_IMPORT
#endif

class DLLAPI_MACBACKWARDFLIPSMOKE2 macbackwardflipsmoke2 : public macsmoke2 {
public:
	macbackwardflipsmoke2();
	virtual ~macbackwardflipsmoke2() {}
protected:
	//
	LONG_NAME("MAC Backward FLIP Smoke 2D")
	MODULE_NAME("macbackwardflipsmoke2")
	//
	virtual void idle() override;
	virtual void draw( graphics_engine &g ) const override;
	virtual void configure( configuration &config ) override;
	//
	bool m_use_regular_velocity_advection;
	macbackwardflip2_driver m_backwardflip{this,"macbackwardflip2"};
};
//
SHKZ_END_NAMESPACE
//
#endif
//
