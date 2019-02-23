
# include "particle_system.h"
# include <sig/gs_string.h>

# include <sigogl/ui_dialogs.h>

//# define GS_USE_TRACE1  // keyword tracing
# include <sig/gs_trace.h>

//======================================== ParticleSystem ===============================================

ParticleSystem::ParticleSystem ()
{
	_time = 0;
	_bounce = true;
	_collides = _collidev = false;
	_gravity.set ( 0, -9.807f, 0 );
	_restitution = 0.5f;
	_colradius = 1.0f;
	_colks=1.0f;
	_colkd=1.0f;
}

ParticleSystem::~ParticleSystem ()
{
}

void ParticleSystem::init ( const char* cfgfile )
{
	GsInput in;
	if ( !cfgfile ) cfgfile = ui_select_file ( "Enter Configuration File", 0, "*.txt" );
	if ( !cfgfile ) gsout.fatal ( "Configuration file needed!" );
	if ( !in.open(cfgfile) ) gsout.fatal ( "Could not open cfg file!");
	_lcfgfile = cfgfile;

	GsVars* params = new GsVars;
	in.commentchar ( '#' );
	in.lowercase ( false );
	while ( true )
	{	if ( in.get()==GsInput::End ) break;
		GS_TRACE1 ( "Token: "<<in.ltoken() );

		if ( in.ltoken()=="parameters" )
		{	in >> *params;
		}
		else if ( in.ltoken()=="end" )
		{	break;
		}
	}
	GS_TRACE1("End Parsing");

	init ( params );
	delete params;
}

void ParticleSystem::init(const GsVars* vars)
{
	int size = vars->geti("particles", 0);

	float mass1 = vars->getf("part.mass", 0);
	float mass2 = vars->getf("part.mass", 1);

	float rest1 = vars->getf("part.restit", 0); if (rest1 <= 0.1f) rest1 = 0.1f;
	float rest2 = vars->getf("part.restit", 1); if (rest2 >= 1.0f) rest2 = 1.0f;

	float vel1 = vars->getf("part.vel", 0);
	float vel2 = vars->getf("part.vel", 1);
	GsVec vel(vars->getf("part.dir", 0), vars->getf("part.dir", 1), vars->getf("part.dir", 2));
	GsString velrand = vars->gets("part.dir.rand");

	_colks = vars->getf("col.ks");
	_colkd = vars->getf("col.kd");

	_restitution = vars->getf("restitution");

	GsVar* v;
	v = vars->get("worldbox");
	_world.set(GsVec(v->getf(0), v->getf(1), v->getf(2)), GsVec(v->getf(3), v->getf(4), v->getf(5)));

	v = vars->get("initpos");
	GsPnt posa(GsVec(v->getf(0), v->getf(1), v->getf(2)));
	GsPnt posb(GsVec(v->getf(3), v->getf(4), v->getf(5)));

	if (scene2) {
		_particles.size(101);
	}

	if (scene3) {
		_particles.size(25);
	}


	if (scene1) {
		_particles.size(3);
	}
	_maxmass = 0;
	_time = 0;

	int i;
	GsQuat q;
	GsVec pos;
	i = 0;
	//for ( i=0; i<1; i++ )
	//{
		//pos.set(0, -30, 0);//gs_random(posa.x,posb.x), gs_random(posa.y,posb.y), gs_random(posa.z,posb.z) );
		//_particles[i].init ( gs_random(mass1,mass2), pos );

		//_particles[i].r = gs_random(rest1,rest2);

		//if ( _particles[i].m>_maxmass ) _maxmass=_particles[i].m;

		//vel.len ( gs_random(vel1,vel2) );
		//_particles[i].v = GsVec(0,0,-1.0f);

		//if ( velrand=="random" )
		//{	GsQuat q;
		//	q.random();
		//	_particles[i].v = q.apply(vel);
		//}
		//i++;

		//pos.set(50, -25, 50);//gs_random(posa.x,posb.x), gs_random(posa.y,posb.y), gs_random(posa.z,posb.z) );
		//_particles[i].init(gs_random(mass1, mass2), pos);

		//_particles[i].r = gs_random(rest1, rest2);

		//if (_particles[i].m>_maxmass) 
		//{
		//	GsQuat q;
		//	q.random();
		//	_particles[i].v = q.apply(vel);
		//}
		//i++;



		/////

	if (scene2) {
		int i = 0;
		for (int x = -15; x < -10; x++)
		{
			for (int z = -15; z < -10; z++)
			{
				pos.set(float(x * 4), -30.0f, float(z * 4));
				_particles[i].init(gs_random(mass1, mass2), pos);
				_particles[i].r = gs_random(rest1, rest2);

				if (_particles[i].m > _maxmass) _maxmass = _particles[i].m;

				//	vel.len(gs_random(vel1, vel2));
				_particles[i].v = GsVec(0, 0, 0);// vel;

				if (velrand == "random")
				{
					GsQuat q;
					q.random();
					_particles[i].v = q.apply(vel);
				}
				i++;
			}
		}


		for (int x = -15; x < -10; x++)
		{
			for (int z = 10; z < 15; z++)
			{
				pos.set(float(x * 4), -30.0f, float(z * 4));
				_particles[i].init(gs_random(mass1, mass2), pos);
				_particles[i].r = gs_random(rest1, rest2);

				if (_particles[i].m > _maxmass) _maxmass = _particles[i].m;

				//	vel.len(gs_random(vel1, vel2));
				_particles[i].v = GsVec(0, 0, 0);// vel;

				if (velrand == "random")
				{
					GsQuat q;
					q.random();
					_particles[i].v = q.apply(vel);
				}
				i++;
			}
		}


		for (int x = 10; x < 15; x++)
		{
			for (int z = -15; z < -10; z++)
			{
				pos.set(float(x * 4), -30.0f, float(z * 4));
				_particles[i].init(gs_random(mass1, mass2), pos);
				_particles[i].r = gs_random(rest1, rest2);

				if (_particles[i].m > _maxmass) _maxmass = _particles[i].m;

				//	vel.len(gs_random(vel1, vel2));
				_particles[i].v = GsVec(0, 0, 0);

				if (velrand == "random")
				{
					GsQuat q;
					q.random();
					_particles[i].v = q.apply(vel);
				}
				i++;
			}
		}


		for (int x = 10; x < 15; x++)
		{
			for (int z = 10; z < 15; z++)
			{
				pos.set(float(x * 4), -30.0f, float(z * 4));
				_particles[i].init(gs_random(mass1, mass2), pos);
				_particles[i].r = gs_random(rest1, rest2);

				if (_particles[i].m > _maxmass) _maxmass = _particles[i].m;

				//	vel.len(gs_random(vel1, vel2));
				_particles[i].v = GsVec(0, 0, 0);

				if (velrand == "random")
				{
					GsQuat q;
					q.random();
					_particles[i].v = q.apply(vel);
				}
				i++;
			}
		}


		pos.set(-10, -30, -80);
		_particles[i].init(gs_random(mass1, mass2), pos);
		_particles[i].r = gs_random(rest1, rest2);

		if (_particles[i].m > _maxmass) _maxmass = _particles[i].m;

		//	vel.len(gs_random(vel1, vel2));
		_particles[i].v = GsVec(0, 0, 0);// vel;

		if (velrand == "random")
		{
			GsQuat q;
			q.random();
			_particles[i].v = q.apply(vel);
		}
		i++;
	}

	//gsout << scene1 << gsnl;
	//gsout << scene2 << gsnl;

	else if (scene3) {


		/*for (int x = 10; x < 15; x++)
		{*/
			for (int i = 0; i < _particles.size(); i++)
			{
				//pos.set(float(x * 4), -30.0f, float(z * 4));
				
				pos.set(gs_random(-40,40),-23, gs_random(-40, 40));
				_particles[i].init(gs_random(mass1, mass2), pos);
				_particles[i].r = gs_random(rest1, rest2);

				if (_particles[i].m > _maxmass) _maxmass = _particles[i].m;

				//	vel.len(gs_random(vel1, vel2));
				_particles[i].v = GsVec(0, 0, 0);

				if (velrand == "random")
				{
					GsQuat q;
					q.random();
					_particles[i].v = q.apply(vel);
				}
				
			}

		//	pos.set(-10, -30, -80);
		//	_particles[i].init(gs_random(mass1, mass2), pos);
		//	_particles[i].r = gs_random(rest1, rest2);

		//	if (_particles[i].m > _maxmass) _maxmass = _particles[i].m;

		//	//	vel.len(gs_random(vel1, vel2));
		//	_particles[i].v = GsVec(0, 0, 0);// vel;

		//	if (velrand == "random")
		//	{
		//		GsQuat q;
		//		q.random();
		//		_particles[i].v = q.apply(vel);
		//	}
		//	i++;
		///*}*/


	}


	else if (scene1) {



		pos.set(-50, -25, 50);//gs_random(posa.x,posb.x), gs_random(posa.y,posb.y), gs_random(posa.z,posb.z) );
		_particles[i].init(gs_random(mass1, mass2), pos);

		_particles[i].r = gs_random(rest1, rest2);

		if (_particles[i].m>_maxmass) _maxmass = _particles[i].m;

		vel.len(gs_random(vel1, vel2));
		_particles[i].v = GsVec(0, 0, -1.0f);

		if (velrand == "random")
		{
			GsQuat q;
			q.random();
			_particles[i].v = q.apply(vel);
		}
		i++;


		

			pos.set(30, -25, -50);//gs_random(posa.x,posb.x), gs_random(posa.y,posb.y), gs_random(posa.z,posb.z) );
		_particles[i].init(gs_random(mass1, mass2), pos);

		_particles[i].r = gs_random(rest1, rest2);

		if (_particles[i].m>_maxmass) _maxmass = _particles[i].m;

		vel.len(gs_random(vel1, vel2));
		_particles[i].v = GsVec(0, 0,0);

		if (velrand == "random")
		{
			GsQuat q;
			q.random();
			_particles[i].v = q.apply(vel);
		}
		i++;


		pos.set(50, -25, 50);//gs_random(posa.x,posb.x), gs_random(posa.y,posb.y), gs_random(posa.z,posb.z) );
		_particles[i].init(gs_random(mass1, mass2), pos);

		_particles[i].r = gs_random(rest1, rest2);

		if (_particles[i].m>_maxmass) _maxmass = _particles[i].m;

		vel.len(gs_random(vel1, vel2));
		_particles[i].v = GsVec(0, 0, -3.0f);

		if (velrand == "random")
		{
			GsQuat q;
			q.random();
			_particles[i].v = q.apply(vel);
		}
		i++;


	}

	//}
}

void ParticleSystem::get_state ()
{
	_state.size ( _particles.size()*6 );
	float* s = &_state[0];
	for ( int i=0, size=_particles.size(); i<size; i++ )
    {	Particle& p = _particles[i];
		*(s++)=p.x.x; *(s++)=p.x.y; *(s++)=p.x.z;
		*(s++)=p.v.x; *(s++)=p.v.y; *(s++)=p.v.z;
	}
}

void ParticleSystem::set_state ()
{
	const float* s = &_state[0];
	for ( int i=0, size=_particles.size(); i<size; i++ )
	{	Particle& p = _particles[i];
		p.x.x=*(s++); p.x.y=*(s++); p.x.z=*(s++);
		p.v.x=*(s++); p.v.y=*(s++); p.v.z=*(s++);
	}
}


GsVec ParticleSystem::collision_offset(int a) {

	GsVec vf, ahead, ahead2, max_ahead, offsetVel = GsVec(0, 0, 0), immideateThreat = GsVec(1000,1000,1000);;
	
	//
	vf = _particles[a].v;
	vf.normalize();
	ahead = _particles[a].x + vf * 1;
	//ahead = position + normalize(velocity) * MAX_SEE_AHEAD
	ahead2 = _particles[a].x + vf * 2 * 0.5;
	float dist;

	for (int i = 0; i < _particles.size(); i++) {

	
	if (i == a) continue;


	
	dist = ::dist(ahead, _particles[i].x);
	
	if (dist < 1.0f) {
		GsVec nt;

		immideateThreat = _particles[i].x;

		offsetVel = ahead - _particles[i].x;
		offsetVel.normalize();
		offsetVel=offsetVel*2;

		break;
	}
	}



	return offsetVel;



}


//void ParticleSystem::collision_avoidance() {
//
//	GsVec ahead, ahead2, max_ahead;
//
//	for (int i = 1; i < 100; i++) {
//
//		ahead = _particles[i].x + _particles[i].v.normalize * 2;
//	//ahead = position + normalize(velocity) * MAX_SEE_AHEAD
//		ahead2 = _particles[i].x + _particles[i].v.normalize * 2 * 0.5;
//
//		//check collision ahead
//
//		check_ahead();
//}
//}
//
//
//
//
//void ParticleSystem::check_ahead(int i) {
//
//	float dist;
//
//	for (int j = 0; j < 100; i++) {
//		if (j == i) break;
//		dist = ::dist(_particles[i], _particles[j]);
//
//
//	}
//
//
//}

//private function distance(a :Object, b : Object) :Number{
//	return Math.sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
//}
//
//void intersect(GsVec ahead, GsVec ahead2) : Boolean{
//	// the property "center" of the obstacle is a Vector3D.
//	return distance(obstacle.center, ahead) <= obstacle.radius || distance(obstacle.center, ahead2) <= obstacle.radius;
//}




void ParticleSystem::compute_derivatives()
{

	clear_forces();
	compute_forces();
	_derivatives.size(_particles.size() * 6);
	float* s = &_derivatives[0];










	if (scene2) {


		GsVec steerigVel, steeringVel1, steeringVel2, steeringVel3, steeringVel4, targetPos;
		targetPos = GsVec(-1.5f, -30, -1.5f);
		// , -25, -50);

		

		if (seek) {


			int i = 24;
			int k = 45;
			int l = 54;
			int m = 75;
			steeringVel1 = seek_vel(targetPos, i)*velScale;
			targetPos = GsVec(-1.5f, -30, 1.5f);

			steeringVel2 = seek_vel(targetPos, k);
			targetPos = GsVec(1.5f, -30, -1.5f);
			steeringVel3 = seek_vel(targetPos, l);
			targetPos = GsVec(1.5f, -30, 1.5f);
			steeringVel4 = seek_vel(targetPos, m);
		}

		if (attack) {
			targetPos = GsVec(20, -25, -50);


			for (int i = 0, size = _particles.size(); i < size; i++)
			{
				Particle& p = _particles[i];
				p.v = GsVec(0, 0, 0);
			}

			int i = 24;

			steeringVel1 = seek_vel(targetPos, i);


			steeringVel2 = seek_vel(targetPos, i);

			steeringVel3 = seek_vel(targetPos, i);

			steeringVel4 = seek_vel(targetPos, i);



			GsVec vel(1, 0, 2);

			float dist;

			dist = ::dist(targetPos, _particles[24].x);


			if (dist < 6.0f) {

				float vel1 = 2.0f;
				float vel2 = 10.0f;
				vel.len(gs_random(vel1, vel2));
				_particles[100].v = GsVec(-7, 0, 2);
				vel = _particles[100].v;

				if (1)
				{
					GsQuat q;
					q.random();
					_particles[100].v = q.apply(vel);
				}
			}
		}


		if (flee) {

			targetPos = GsVec(20, -25, -50);

			int i = 24;

			steeringVel1 = -seek_vel(targetPos, i);


			steeringVel2 = -seek_vel(targetPos, i);

			steeringVel3 = -seek_vel(targetPos, i);

			steeringVel4 = -seek_vel(targetPos, i);
		}

		/* if (persue) {
			int i = 20;
			steeringVel1 = persue_vel(_particles[100].x, i);



		}*/


		
		//persue

		if (persue) {

			GsVec steeringVel, offsetVel;
			//float dist1 = ::dist(_particles[100].x, _particles[99].x);

			/*for (int i = 90, size = _particles.size(); i < 100; i++)
			{*/
			for(int i=0;i<5;i++){
				Particle& p = _particles[0];

				//int i = 0;
				float dist1 = ::dist(_particles[100].x, _particles[i].x);


				offsetVel = collision_offset(i);





				steeringVel = persue_vel(_particles[100].x, i); //+ offsetVel;
				steeringVel = steeringVel * velScale;

				if (dist1 < 2.0f) {
					//if (persue) {
					*(s++) = 0.0f;//steeringVel.x;//p.v.x;
					*(s++) = 0.0f;//p.v.y;
					*(s++) = 0.0f;//steeringVel.z; //p.v.z;


				}
				else {
					*(s++) = steeringVel.x;//p.v.x;
					*(s++) = 0.0f;//p.v.y;
					*(s++) = steeringVel.z; //p.v.z;
				}
				/*}

				else {
					*(s++) = p.v.x;
					*(s++) = p.v.y;
					*(s++) = p.v.z;
				}

				else {
					*(s++) = p.v.x;
					*(s++) = p.v.y;
					*(s++) = p.v.z;
				}*/
				*(s++) = p.f.x / p.m;
				*(s++) = p.f.y / p.m;
				*(s++) = p.f.z / p.m;
			}


			for (int i = 5, size = _particles.size(); i < 100; i++)
			{
				Particle& p = _particles[i];

				///*if (seek || persue || flee || attack) {*/
				//	*(s++) = steeringVel4.x;//p.v.x;
				//	*(s++) = 0.0f;//p.v.y;
				//	*(s++) = steeringVel4.z; //p.v.z;
				///*}
				//else {
				*(s++) = p.v.x;
				*(s++) = p.v.y;
				*(s++) = p.v.z;
				///*}*/*/
				*(s++) = p.f.x / p.m;
				*(s++) = p.f.y / p.m;
				*(s++) = p.f.z / p.m;
			}

			for (int i = 100, size = _particles.size(); i < size; i++)
			{
				float dist5, fd=1000;
				//for (int i = 90; i < 100; i++) {

				dist5 = ::dist(_particles[0].x, _particles[100].x);

				//if (dist5 < 1.0f) {
				//	//gsout << dist5 << gsnl;
				//	//gsout << fd << gsnl;
				//	fd = dist5;
				//	//break;
				//}
				//gsout << dist5 << gsnl;
				//gsout << fd << gsnl;
				//}

				

				Particle& p = _particles[i];


				if (dist5 < 3.0f) {
					//if (persue) {
					*(s++) = 0.0f;//steeringVel.x;//p.v.x;
					*(s++) = 0.0f;//p.v.y;
					*(s++) = 0.0f;//steeringVel.z; //p.v.z;


				}
				else {
					*(s++) = p.v.x;
					*(s++) = p.v.y;
					*(s++) = p.v.z;
				}

				*(s++) = p.v.x;
				*(s++) = p.v.y;
				*(s++) = p.v.z;
				*(s++) = p.f.x / p.m;
				*(s++) = p.f.y / p.m;
				*(s++) = p.f.z / p.m;
			}


		}

		///end persue

		else {

			for (int i = 0, size = _particles.size(); i < 25; i++)
			{
				Particle& p = _particles[i];

				if (seek || flee || attack) {
					*(s++) = steeringVel1.x;//p.v.x;
					*(s++) = 0.0f;//p.v.y;
					*(s++) = steeringVel1.z; //p.v.z;
				}
				else {
					*(s++) = p.v.x;
					*(s++) = p.v.y;
					*(s++) = p.v.z;
				}
				*(s++) = p.f.x / p.m;
				*(s++) = p.f.y / p.m;
				*(s++) = p.f.z / p.m;
			}

			for (int i = 25, size = _particles.size(); i < 50; i++)
			{
				Particle& p = _particles[i];

				if (seek || flee || attack) {
					*(s++) = steeringVel2.x;//p.v.x;
					*(s++) = 0.0f;//p.v.y;
					*(s++) = steeringVel2.z; //p.v.z;
				}
				else {
					*(s++) = p.v.x;
					*(s++) = p.v.y;
					*(s++) = p.v.z;
				}
				*(s++) = p.f.x / p.m;
				*(s++) = p.f.y / p.m;
				*(s++) = p.f.z / p.m;
			}

			for (int i = 50, size = _particles.size(); i < 75; i++)
			{
				Particle& p = _particles[i];

				if (seek || flee || attack) {
					*(s++) = steeringVel3.x;//p.v.x;
					*(s++) = 0.0f;//p.v.y;
					*(s++) = steeringVel3.z; //p.v.z;
				}
				else {
					*(s++) = p.v.x;
					*(s++) = p.v.y;
					*(s++) = p.v.z;
				}
				*(s++) = p.f.x / p.m;
				*(s++) = p.f.y / p.m;
				*(s++) = p.f.z / p.m;
			}

			for (int i = 75, size = _particles.size(); i < 100; i++)
			{
				Particle& p = _particles[i];

				if (seek || flee || attack) {
					*(s++) = steeringVel4.x;//p.v.x;
					*(s++) = 0.0f;//p.v.y;
					*(s++) = steeringVel4.z; //p.v.z;
				}
				else {
					*(s++) = p.v.x;
					*(s++) = p.v.y;
					*(s++) = p.v.z;
				}
				*(s++) = p.f.x / p.m;
				*(s++) = p.f.y / p.m;
				*(s++) = p.f.z / p.m;
			}
			for (int i = 100, size = _particles.size(); i < size; i++)
			{
				Particle& p = _particles[i];


				*(s++) = p.v.x;
				*(s++) = p.v.y;
				*(s++) = p.v.z;
				*(s++) = p.f.x / p.m;
				*(s++) = p.f.y / p.m;
				*(s++) = p.f.z / p.m;
			}
		}

	}




	else if (scene1) {

		for (int i = 0, size = _particles.size(); i < size; i++)
		{
			Particle& p = _particles[i];


			*(s++) = p.v.x;
			*(s++) = p.v.y;
			*(s++) = p.v.z;
			*(s++) = p.f.x / p.m;
			*(s++) = p.f.y / p.m;
			*(s++) = p.f.z / p.m;
		}

	}

	else if (scene3) {
		for (int i = 0, size = _particles.size(); i < size; i++)
		{
			Particle& p = _particles[i];


			*(s++) = p.v.x;
			*(s++) = p.v.y;
			*(s++) = p.v.z;
			*(s++) = p.f.x / p.m;
			*(s++) = p.f.y / p.m;
			*(s++) = p.f.z / p.m;
		}

	}

}













void ParticleSystem::clear_forces ()
{
	for ( int i=0, size=_particles.size(); i<size; i++ )
	{	_particles[i].f = GsVec::null;
	}
}


GsVec ParticleSystem::seek_vel(GsVec targetPos, int i){

	GsVec desiredPos, desiredVel, steeringVel;

	float maxVel;
		if (persue||persue2) {
			maxVel= 10.0f;

		}
		else
			maxVel = 5.0f;
	//float distance;

	
		desiredPos = targetPos - _particles[i].x;//visa-vi

		//desiredPos =_particles[0].x-targetPos;

	//	gsout << desiredPos << gsnl;
		//distance = ::dist(targetPos, _particles[0].x);

		desiredPos.normalize();
		desiredVel = desiredPos * maxVel;

		steeringVel = desiredVel - _particles[i].v;

	//	gsout << steeringVel << gsnl;

		return steeringVel;

	
	}

GsVec ParticleSystem::persue_vel(GsVec targetPos, int i) {

	GsVec futurePos,steeringV;
	float a,dist;

	dist = ::dist(_particles[i].x, _particles[_particles.size()-1].x);
	a = dist / 5;
	futurePos = _particles[_particles.size() - 1].x +_particles[_particles.size() - 1].v*a;
	//rand
	/*if (dist > 2.0f) {
		steeringV = seek_vel(futurePos, i)*gs_random(1.0f, 5.0f);
	}
	else*/
		steeringV = seek_vel(futurePos, i);// *gs_random(1.0f, 3.0f);
	return steeringV;
	// velocity of the target particle, velocity of current particle

}


void ParticleSystem::compute_forces ()
{
	int i, j, size=_particles.size();

	for ( i=0; i<size; i++ )
	{	//_particles[i].f += (_particles[i].m*_gravity) + _extforce;
	_particles[i].f += _extforce;
	}

	if ( 0 )
	{
		float dist, r2 = 3.0f;// _colradius*2.0f;
		GsVec l, dv, f;

		for ( i=0; i<size; i++ )
		{
			for ( j=0; j<size; j++ )
			{	if ( i==j) continue;
				dist = ::dist(_particles[i].x,_particles[j].x);
				if (  dist<r2 )
				{	l = _particles[i].x-_particles[j].x;
					dv = _particles[i].v-_particles[j].v;
					f = l / dist * -( _colks*(dist-r2) + dot(dv,l)*_colkd/dist); // spring behavior
					_particles[i].f += f;

					/*GsVec n = l; n.normalize();
					f = _particles[i].f;
					_particles[i].f += -f*dot(n,f);*/
				}
			}
		}
	}

	if ( 0 )
	{	GsVec n = GsVec::j; // bottom plane normal pointing up
		GsVec v, nv;
		for ( i=0; i<size; i++ )
		{	// we do something simple here with the "floor":
			if ( _particles[i].x.y<_world.a.y  &&  dot(_particles[i].v,n)<0 )
			{	//_particles[i].v = reflect(n,_particles[i].v) * _restitution * _particles[i].r;
				GsVec f = _particles[i].f;
				_particles[i].f += f * -dot(f,n);
			}
		}
	}

}

inline GsVec reflect ( const GsVec& n, const GsVec& v )
{
	GsVec nv, tv;
	nv = n * dot ( v, n ); // normal component
	tv = v - nv;           // tangential component
	return tv-nv;
}

void ParticleSystem::euler_step ( float deltat )
{
	compute_derivatives ();
	int i, stsize=_derivatives.size();
	GsVec steeringVel;

	for ( i=0; i<stsize; i++ ) _derivatives[i]*=deltat;
	get_state ();
	for ( i=0; i<stsize; i++ ) _state[i]+=_derivatives[i];

	set_state ();

	_time += deltat;



	if (scene3) {

		GsVec target = GsVec(0,-25,0), offsetVel;
		//target2 = _particles[_particles.size() - 2].x;

		float dist;// = ::dist(_particles[_particles.size() - 2].x, _particles[_particles.size() - 1].x);

		
		if (seek) {
		for (i = 0; i < _particles.size(); i++) {
			offsetVel = collision_offset(i);
			 dist = ::dist(_particles[i].x, target);

			

				if (dist>10.0f) {
					//gsout << dist << gsnl;
					steeringVel = seek_vel(target, i);// *velScale;

					steeringVel = seek_vel(target, i);// *velScale;
					steeringVel += offsetVel;
					_particles[i].v += GsVec(steeringVel.x, 0, steeringVel.z);
				}


				else {


					_particles[i].v = GsVec(0, 0, 0);


				}

				//_particles[25].v = GsVec(0, 0, 0);
			}

		}




		if (attack) {

			target = GsVec(20, -25, -50);

			//_particles[_particles.size() - 1].v = GsVec(1, 0, 2);

			for (i = 0; i < _particles.size(); i++) {
				offsetVel = collision_offset(i);
				dist = ::dist(_particles[i].x, target);

				steeringVel = seek_vel(target, i);// *velScale;
				steeringVel += offsetVel;
				_particles[i].v += GsVec(steeringVel.x, 0, steeringVel.z);
			}



		}


		else if (persue) {

		
			target = _particles[_particles.size()].x;

			//_particles[_particles.size()].v = GsVec(1, 0, 2);

			for (i = 0; i < _particles.size() - 1; i++) {
				offsetVel = collision_offset(i);
				dist = ::dist(_particles[i].x, target);

				steeringVel = seek_vel(target, i);// *velScale;
				steeringVel += offsetVel;
				_particles[i].v += GsVec(steeringVel.x, 0, steeringVel.z);
			}


		}
	}



	if (scene1) {
		GsVec target = _particles[_particles.size() - 1].x, target2;
		target2 = _particles[_particles.size() - 2].x;

		float dist = ::dist(_particles[0].x, _particles[_particles.size() - 1].x);

		if (!persue|| !persue2) {
			
			_particles[_particles.size() - 2].v = GsVec(0, 0, 0);
		
		_particles[_particles.size() - 1].v = GsVec(0, 0, 0);
		}

		else if (persue||persue2) {

			_particles[_particles.size() - 1].v = GsVec(0, 0, -3);
		}

		for (i = 0; i < _particles.size()-2; i++) {
			

			if (persue) {

				if (dist < 4.0f) {
					_particles[_particles.size() - 1].v = GsVec(0, 0, 0);

					steeringVel = seek_vel(target, i);// *velScale;
					_particles[2].v = GsVec(0, 0, 0);
					_particles[i].v = GsVec(0, 0, 0);
				}


				else{
					_particles[_particles.size() - 1].v = GsVec(0, 0, -3);

					steeringVel = seek_vel(target, i);// *velScale;

					_particles[i].v += steeringVel;
				}
			}

			else if (persue2) {
				//_particles[_particles.size() - 1].v = GsVec(0, 0, -3);

				//steeringVel = persue_vel(target, i);

				//_particles[i].v += steeringVel;// *velScale;

				if (dist < 4.0f) {
					_particles[_particles.size() - 1].v = GsVec(0, 0, 0);

					steeringVel = persue_vel(target, i);// *velScale;

					_particles[i].v = GsVec(0, 0, 0);
				}


				else {
					_particles[_particles.size() - 1].v = GsVec(0, 0, -3);

					steeringVel = persue_vel(target, i);// *velScale;

					_particles[i].v += steeringVel;
				}

			}

			else if (seek) {

				steeringVel = seek_vel(target2, i);

				_particles[i].v += steeringVel;

			}

			else if (flee) {

				steeringVel = seek_vel(target, i);

				_particles[i].v -= steeringVel;

			}

		}
	}



	if ( seek && scene3  )
	{	float dist, r2=_colradius*2.0f; 
		GsVec n, v, steeringVel, targetPos;
		targetPos = GsVec(20, -25, -50);

		int i, j, psize=_particles.size();


		//steeringVel = seek_vel(targetPos, i);
		for ( i=0; i<psize-1; i++ )
		{ 
			for ( j=0; j<psize-1; j++ )
			{	if ( i==j) continue;
				dist = ::dist(_particles[i].x,_particles[j].x);
				if ( dist<2.0f )
				{	n = _particles[i].x-_particles[j].x;
					n.normalize();
					v=_particles[i].v;
					v.normalize();
				if (dot(n, v) < 0)
						_particles[i].v = reflect(n, _particles[i].v); //;* _restitution * _particles[i].r;
				}
			}
		}
	}

	// to try: bounce against all planes!
	if ( 0 )
	{	GsVec n = GsVec::j; // bottom plane normal pointing up
		GsVec v, nv;
		for ( i=0; i<_particles.size(); i++ )
		{	// we do something simple here with the "floor":
			if ( _particles[i].x.y<_world.a.y  &&  dot(_particles[i].v,n)<0 )
			{	_particles[i].v = reflect(n,_particles[i].v) * _restitution * _particles[i].r;
			}
		}
	}

}

//======================================== EOF ===============================================
