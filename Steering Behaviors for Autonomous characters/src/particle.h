
# pragma once

# include <sig/gs_vec.h>

class Particle
 { public :
	float m;  // mass
	GsVec x;  // position
	GsVec v;  // velocity
	GsVec f;  // force accumulator
	float r;  // coeff restitution
	GsVec steeringV;

   public :
	void init ( float mass, const GsVec& pos )
	{
		m = mass; x = pos; steeringV = GsVec::null; v = GsVec::null; f = GsVec::null; r = 1.0f;
	}
};
