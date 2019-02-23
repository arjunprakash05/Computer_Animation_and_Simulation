
# pragma once

# include <sig/gs_array.h>
# include <sig/gs_box.h>
# include <sig/gs_quat.h>
# include <sig/gs_vars.h>

# include "particle.h"

class ParticleSystem
 { private :
	GsArray<Particle> _particles;
	GsArray<float> _state;
	GsArray<float> _state1;

	GsArray<float> _derivatives;
	float _time;
	GsVec _extforce;
	GsVec _gravity;
	GsBox _world;
	GsPnt _initpos;
	bool _bounce;
	bool _collides, _collidev;
	float _colradius;
	float _colks;
	float _colkd;
	float _restitution;
	float _maxmass;
	GsCharPt _lcfgfile;

   public :
	ParticleSystem ();
   ~ParticleSystem ();

	const char* last_cfg_file () const { return _lcfgfile; }

	void init ( const char* cfgfile );
	void init ( const GsVars* vars );

	void bounce ( bool b ) { _bounce=b; }
	void spring_collision_prevention ( bool sc ) { _collides=sc; }
	void velocity_collision_prevention ( bool vc ) { _collidev=vc; }
	void coeff_restitution ( float r ) { _restitution=r; }
	float coeff_restitution () { return _restitution; }

	void external_force ( const GsVec& f ) { _extforce=f; }
	void collision_radius ( float r ) { _colradius=r; }

	const GsArray<Particle>& particles() const { return _particles; }
	const GsBox& world() const { return _world; }

	void get_state ();
	void set_state ();
	void clear_forces ();
	void compute_forces ();
	void compute_derivatives ();

	void compute_derivatives_for_midpoint();

	void euler_step ( float deltat );
	void mid_point_step(float deltat);
};
