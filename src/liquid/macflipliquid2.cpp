/*
**	macflipliquid2.cpp
**
**	This is part of Shiokaze, a research-oriented fluid solver for computer graphics.
**	Created by Ryoichi Ando <rand@nii.ac.jp> on April 17, 2017. 
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
#include "macflipliquid2.h"
#include <shiokaze/array/shared_array2.h>
#include <shiokaze/array/shared_bitarray2.h>
#include <shiokaze/array/macarray_extrapolator2.h>
#include <shiokaze/array/macarray_interpolator2.h>
#include <shiokaze/array/array_upsampler2.h>
#include <shiokaze/array/array_interpolator2.h>
#include <shiokaze/utility/utility.h>
#include <cmath>
//
SHKZ_USING_NAMESPACE
//
macflipliquid2::macflipliquid2 () {
	m_param.PICFLIP = 0.95;
}
//
void macflipliquid2::configure( configuration &config ) {
	//
	config.get_double("PICFLIP",m_param.PICFLIP,"PICFLIP blending factor");
	assert( m_param.PICFLIP >= 0.0 && m_param.PICFLIP <= 1.0 );
	//
	macliquid2::configure(config);
	//
	m_double_shape = 2 * m_shape;
	m_half_dx = 0.5 * m_dx;
	//
	config.set_default_double("HighresRasterizer.RadiusFactor",1.0);
	config.set_default_double("HighresRasterizer.WeightFactor",2.0);
	config.set_default_unsigned("HighresRasterizer.NeighborLookUpCells",2);
	//
	m_highres_particlerasterizer->set_environment("shape",&m_double_shape);
	m_highres_particlerasterizer->set_environment("dx",&m_half_dx);
	//
	m_highres_gridvisualizer->set_environment("shape",&m_double_shape);
	m_highres_gridvisualizer->set_environment("dx",&m_half_dx);
}
//
void macflipliquid2::post_initialize () {
	//
	macliquid2::post_initialize();
	extend_both();
	m_flip->seed(m_fluid,[&](const vec2d &p){ return interpolate_solid(p); },m_velocity);
}
//
void macflipliquid2::idle() {
	//
	// Compute the timestep size
	double dt = m_timestepper->advance(m_macutility->compute_max_u(m_velocity),m_dx);
	unsigned step = m_timestepper->get_step_count();
	//
	shared_macarray2<float> face_density(m_shape);
	shared_macarray2<float> save_velocity(m_shape);
	shared_macarray2<float> momentum(m_shape);
	shared_macarray2<float> mass(m_shape);
	//
	// Update fluid levelset
	m_flip->update([&](const vec2d &p){ return interpolate_solid(p); },m_fluid);
	//
	// Advect fluid levelset
	m_macsurfacetracker->advect(m_fluid,m_solid,m_velocity,dt);
	//
	// Advect FLIP particles
	m_flip->advect(
		[&](const vec2d &p){ return interpolate_solid(p); },
		[&](const vec2d &p){ return interpolate_velocity(p); },
		m_timestepper->get_current_time(),dt);
	//
	// Grid velocity advection
	m_macadvection->advect_vector(m_velocity,m_velocity,m_fluid,dt);
	//
	// Mark bullet particles
	m_flip->mark_bullet(
		[&](const vec2d &p){ return interpolate_fluid(p); },
		[&](const vec2d &p){ return interpolate_velocity(p); },
		m_timestepper->get_current_time()
	);
	//
	// Correct positions
	m_flip->correct([&](const vec2d &p){ return interpolate_fluid(p); });
	//
	// Reseed particles
	m_flip->seed(m_fluid,
		[&](const vec2d &p){ return interpolate_solid(p); },
		m_velocity
	);
	//
	// Splat momentum and mass of FLIP particles onto grids
	m_flip->splat(momentum(),mass());
	//
	// Compute face mass
	m_macutility->compute_face_density(m_solid,m_fluid,face_density());
	//
	// Compute the combined grid velocity
	shared_macarray2<float> overwritten_velocity(m_shape);
	overwritten_velocity->activate_as(mass());
	overwritten_velocity->parallel_actives([&](int dim, int i, int j, auto &it, int tn ) {
		double m = mass()[dim](i,j);
		double grid_mass = std::max(0.0,face_density()[dim](i,j)-m);
		it.set((grid_mass*m_velocity[dim](i,j)+momentum()[dim](i,j)) / (grid_mass+m));
	});
	//
	// Velocity overwrite
	overwritten_velocity->const_serial_actives([&](int dim, int i, int j, auto &it) {
		m_velocity[dim].set(i,j,it());
	});
	//
	// Save the current velocity
	save_velocity->copy(m_velocity);
	//
	// Add external force
	inject_external_force(m_velocity,dt);
	//
	// Set volume correction
	set_volume_correction(m_macproject.get());
	//
	// Project
	m_macproject->project(dt,m_velocity,m_solid,m_fluid);
	//
	// Extend both the level set and velocity
	extend_both();
	//
	// Update FLIP velocity
	m_flip->update(save_velocity(),m_velocity,dt,(macliquid2::m_param).gravity,m_param.PICFLIP);
	//
	// Report stats
	m_macstats->dump_stats(m_solid,m_fluid,m_velocity,m_timestepper.get());
}
//
double macflipliquid2::interpolate_fluid( const vec2d &p ) const {
	return array_interpolator2::interpolate(m_fluid,p/m_dx-vec2d(0.5,0.5));
}
//
double macflipliquid2::interpolate_solid( const vec2d &p ) const {
	return array_interpolator2::interpolate(m_solid,p/m_dx);
}
//
vec2d macflipliquid2::interpolate_velocity( const vec2d &p ) const {
	return macarray_interpolator2::interpolate(m_velocity,vec2d(),m_dx,p);
}
//
void macflipliquid2::draw_highresolution( graphics_engine &g ) const {
	//
	shared_array2<float> doubled_fluid(m_double_shape.cell(),1.0);
	shared_array2<float> doubled_solid(m_double_shape.nodal(),1.0);
	//
	array_upsampler2::upsample_to_double_cell<float>(m_fluid,m_dx,doubled_fluid());
	array_upsampler2::upsample_to_double_nodal<float>(m_solid,m_dx,doubled_solid());
	//
	shared_bitarray2 mask(m_double_shape);
	shared_array2<float> sizing_array(m_shape);
	//
	std::vector<particlerasterizer2_interface::Particle2> points, ballistic_points;
	std::vector<macflip2_interface::particle2> particles = m_flip->get_particles();
	for( int n=0; n<particles.size(); ++n ) {
		//
		particlerasterizer2_interface::Particle2 point;
		point.p = particles[n].p;
		point.r = particles[n].r;
		double levelset_value = interpolate_fluid(particles[n].p);
		//
		if( levelset_value < 0.5*m_dx ) {
			points.push_back(point);
			mask().set(mask->shape().clamp(point.p/m_half_dx));
		} else {
			if( particles[n].bullet ) ballistic_points.push_back(point);
		}
		//
		vec2i pi = m_shape.find_cell(point.p/m_dx);
		sizing_array->set(pi,std::max((float)particles[n].sizing_value,sizing_array()(pi)));
	}
	//
	mask().dilate(4);
	doubled_fluid->activate_as(mask());
	//
	shared_array2<float> particle_levelset(m_double_shape,0.125*m_dx);
	m_highres_particlerasterizer->build_levelset(particle_levelset(),mask(),points);
	//
	doubled_fluid->parallel_actives([&](int i, int j, auto &it, int tn) {
		double rate = array_interpolator2::interpolate(sizing_array(),0.5*vec2d(i,j));
		double f = it(), p = particle_levelset()(i,j);
		it.set( rate * std::min(f,p) + (1.0-rate) * f );
	});
	//
	// Draw high resolution level set
	m_highres_gridvisualizer->draw_fluid(g,doubled_solid(),doubled_fluid());
	//
	// Draw FLIP
	m_flip->draw(g,m_timestepper->get_current_time());
}
//
void macflipliquid2::draw( graphics_engine &g ) const {
	//
	// Draw grid lines
	m_gridvisualizer->draw_grid(g);
	//
	// Draw simulation
	draw_highresolution(g);
	//
	// Draw projection component
	m_macproject->draw(g);
	//
	// Draw solid levelset
	m_gridvisualizer->draw_solid(g,m_solid);
	//
	// Draw velocity
	m_macvisualizer->draw_velocity(g,m_velocity);
}
//
extern "C" DLLAPI_MACFLIPLIQUID2 module * create_instance() {
	return new macflipliquid2;
}
//
extern "C" const char *license() {
	return "MIT";
}
//