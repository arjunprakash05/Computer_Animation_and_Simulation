
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
	float velScale=1.0f;

	bool seek=0;
	bool persue = 0;
	bool persue2 = 0;
	bool flee = 0;
	bool attack = 0;
	bool gather = 0;
	bool scene1=1;
	bool scene2=0;
	bool scene3=0;

   public :
	ParticleSystem ();
   ~ParticleSystem ();

	const char* last_cfg_file () const { return _lcfgfile; }

	void init ( const char* cfgfile );
	void init ( const GsVars* vars );

	void bounce ( bool b ) { _bounce=b; }

	void seek1(bool s) { seek = s; }
	void persue21(bool s) { persue2 = s; }
	void persue1(bool s) { persue = s; }
	void flee1(bool f) { flee = f; }
	void gather1(bool g) { gather = g; }
	void attack1(bool a) { attack = a; }



	void scene1_(bool a) {scene1 = a; }
	void scene2_(bool x) { scene2 = x; }
	void scene3_(bool z) { scene3 = z; }


	void spring_collision_prevention ( bool sc ) { _collides=sc; }
	void velocity_collision_prevention ( bool vc ) { _collidev=vc; }
	void coeff_restitution ( float r ) { velScale =r; }
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

	GsVec seek_vel(GsVec targetPos, int i);
	GsVec persue_vel(GsVec targetPos, int i);
	GsVec collision_offset( int a);
	//void collision_avoidance();
	//GsVec 

	void euler_step ( float deltat );
};
