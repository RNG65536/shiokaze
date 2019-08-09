/*
**	sysstats.cpp
**
**	This is part of Shiokaze, a research-oriented fluid solver for computer graphics.
**	Created by Ryoichi Ando <rand@nii.ac.jp> on Sep 21, 2017. 
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
#include <shiokaze/system/sysstats_interface.h>
#include <shiokaze/core/cmdparser.h>
#include <shiokaze/core/console.h>
#include <shiokaze/core/timer.h>
#include <shiokaze/core/filesystem.h>
#include <shiokaze/array/shared_array_core2.h>
#include <shiokaze/array/shared_array_core3.h>
#include <string>
//
SHKZ_USING_NAMESPACE
//
class sysstats : public sysstats_interface {
protected:
	//
	MODULE_NAME("sysstats")
	//
	virtual void report_stats() const override {
		console::dump("Arguments: %s\n", arg_str.c_str());
		size_t num_grids2 = shared_array_core2::get_total_grid_count();
		if( num_grids2 ) {
			console::dump("Current total shared 2D grids = %u\n", num_grids2 );
		}
		size_t num_grids3 = shared_array_core3::get_total_grid_count();
		if( num_grids3 ) {
			console::dump("Current total shared 3D grids = %u\n", num_grids3 );
		}
	}
	//
	virtual void plot_graph() const override {
		if( plot_template.size() && console::get_root_path().size() ) {
			scoped_timer timer{this};
			global_timer::pause();
			std::string record_path = console::get_root_path() + "/record";
			std::string record_image_path = console::get_root_path() + "/record/graph_images";
			if( ! filesystem::is_exist(record_image_path)) {
				filesystem::create_directory(record_image_path);
			}
			std::string plot_command = console::format_str(plot_template.c_str(), console::get_root_path().c_str());
			timer.tick(); console::dump( "Plotting graph (%s)...", plot_command.c_str());
			console::system(plot_command);
			console::dump( "Done.\n" );
			global_timer::resume();
		}
	}
	//
	virtual void configure ( configuration &config ) override {
		cmdparser parser(config.get_dictionary());
		arg_str = parser.get_arg_string();
		//if( console::system("gnuplot -V > /dev/null 2>&1") == 0 ) {
		//	plot_template = "cd %s/record; ./plot.sh > /dev/null 2>&1";
		//} else {
			plot_template = "";
		//}
		config.get_string("PlotTemplate",plot_template,"Plot command template");
	}
	//
private:
	std::string arg_str;
	std::string plot_template;
};
//
#ifdef DLLEXPORT_SYSSTATS
#define DLLAPI_SYSSTATS DLLAPI_EXPORT
#else
#define DLLAPI_SYSSTATS DLLAPI_IMPORT
#endif

extern "C" DLLAPI_SYSSTATS module * create_instance() {
	return new sysstats();
}
//
extern "C" const char *license() {
	return "MIT";
}
//