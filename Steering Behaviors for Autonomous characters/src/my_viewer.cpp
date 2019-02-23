
# include "my_viewer.h"

# include <sig/sn_model.h>
# include <sig/sn_material.h>
# include <sig/sn_transform.h>

# include <sigogl/ws_run.h>

# define CHKVAR(s) if(_vars->search(s)<0) { fltk::alert("Missing parameter [%s]!",s); exit(0); }

MyViewer::MyViewer ( int x, int y, int w, int h, const char *l ) : WsViewer ( x, y, w, h, l )
{
	_root = WsViewer::rootg();

	_lines = new SnLines;
	_world = new SnLines;
	_points = new SnPoints;
	_spheres = new SnGroup;
	_targets = new SnGroup;

	view ( false, true, true ); // lines, world, spheres

	_root->add(_lines);
	_root->add(_points);
	_root->add(_world);
	_root->add(_spheres);
  
	_sphereradius = 1.0f;
}

MyViewer::~MyViewer ()
{
}

enum Events {	EvInit,
				EvViewSpheres, EvViewVelVecs,
				EvRun, EvSeek, EvSeek1, EvBounce,
				EvSCollision, EvVCollision, EvTScale, EvCRestitut,
				EvView, EvExit, EvPersue, EvPersue2, EvFlee, EvGather, EvAttack, EvScen1, EvScen2, EvScen3
			}; 

void MyViewer::build_ui ()
{
	UiPanel *p, *sp, *paramsp;
	UiManager* uim = WsWindow::uim();
	bool detachparms = true;

	// Top Menu Bar:
	p = uim->add_panel ( "", UiPanel::HorizLeft );
	p->add ( new UiButton ( "Init", EvInit ) );
	if (!detachparms) p->add ( new UiButton ( "Parameters", sp=new UiPanel() ) ); paramsp=sp;
	p->add ( new UiButton ( "View", sp=new UiPanel() ) );
	{	UiPanel* p=sp;
		p->add ( _vvel = new UiCheckButton ( "Velocities", EvView, false ) ); p->top()->separate();
		p->add ( _vworld = new UiCheckButton ( "World", EvView, true ) ); 
		p->add ( _vsphere = new UiCheckButton ( "Spheres", EvView, true ) ); 
	}

	p->add(new UiButton("Scene", sp = new UiPanel()));
	{	UiPanel* p = sp;
	p->add(_scenario1 = new UiCheckButton("Scenario1", EvScen1, false));
	p->add(_scenario2 = new UiCheckButton("Scenario2", EvScen2,false));
	p->add(_scenario3 = new UiCheckButton("Scenario3", EvScen3,false));
	}


	p->add ( new UiButton ( "Exit", EvExit ) );

	if (!detachparms) p = paramsp; // build parameters panel now
	else p = uim->add_panel ( "Parameters", UiPanel::Vertical, UiPanel::Left, 0, 30 );

	p->add ( _run = new UiCheckButton ( "Run", EvRun ) );
	p->add(_seek1 = new UiCheckButton("Seek", EvSeek1));
	p->add ( _seek = new UiCheckButton ( "Gather", EvSeek ) ); 
		p->add(_attack = new UiCheckButton("Attack", EvAttack));
	p->add(_flee = new UiCheckButton("Flee", EvFlee));
	p->add(_persue= new UiCheckButton("Pursue1", EvPersue));
	p->add(_persue2 = new UiCheckButton("Pursue2", EvPersue2));

	/*p->add(_gather = new UiCheckButton("Gather", EvGather));
	p->add ( _scol = new UiCheckButton ( "Spring-Based Collision", EvSCollision ) );
	p->add ( _vcol = new UiCheckButton ( "Vel. Reflection Collision", EvVCollision ) );
	p->add ( _bounce = new UiCheckButton ( "Bounce", EvBounce ) ); _bounce->value(true);
*/
	//p->add ( new UiElement("Wind Force:") ); p->top()->separate();
	//p->add ( _windslider = new UiSlider("", EvSeek) );
	//_windslider->range(-5.0f,5.0f);

	p->add(new UiElement("Velocity:"));
	p->add(_crestslider = new UiSlider("", EvCRestitut));

	_crestslider->range(0.01f, 20.0f); _crestslider->value(1.0f);

	p->add ( new UiElement("Time Scale:") ); 
	p->add ( _tscaleslider = new UiSlider("", EvTScale) );
	_tscaleslider->range(0.01f,4.0f); _tscaleslider->value(1.0f);

	/*p->add ( new UiElement("Coeff. of Restitution:") ); 
  p->add ( _crestslider = new UiSlider("", EvCRestitut) );*/
}

void MyViewer::view ( bool vel, bool world, bool spheres )
{
	_lines->visible ( vel );
	_world->visible ( world );
	_spheres->visible ( spheres );
	_points->visible ( !spheres );
}

void MyViewer::build_scene ( ParticleSystem& psys, int nfaces )
{
	const GsArray<Particle>& p = psys.particles();
	int i, psize=p.size();
	_psys = &psys;
	_nfaces = nfaces;

	//_crestslider->value ( _psys->coeff_restitution() );



	

	SnModel* sphere = new SnModel;
	sphere->model()->make_sphere ( GsPnt::null, 1.0f, nfaces, true );

	SnGroup* g;
	SnTransform* t;
	SnMaterial* m;


	//scene 1

	if (_scenario2->value()) {


		_root->add(_targets);
		//green army
		_spheres->init();
		_positions.size(0); // fast access to later update positions
		for (i = 0; i < 25; i++)
		{
			_spheres->add(g = new SnGroup);
			g->separator(true); // transformations inside group do not affect outside group
			g->add(t = new SnTransform);
			g->add(m = new SnMaterial);
			g->add(sphere);
			_positions.push() = &(t->get());
			t->get().translation(p[i].x);
			m->material().diffuse = GsColor::green;
		}


		///red army

		for (i = 25; i < 50; i++)
		{
			_spheres->add(g = new SnGroup);
			g->separator(true); // transformations inside group do not affect outside group
			g->add(t = new SnTransform);
			g->add(m = new SnMaterial);
			g->add(sphere);
			_positions.push() = &(t->get());
			t->get().translation(p[i].x);
			m->material().diffuse = GsColor::red;
		}

		//blue army

		for (i = 50; i < 75; i++)
		{
			_spheres->add(g = new SnGroup);
			g->separator(true); // transformations inside group do not affect outside group
			g->add(t = new SnTransform);
			g->add(m = new SnMaterial);
			g->add(sphere);
			_positions.push() = &(t->get());
			t->get().translation(p[i].x);
			m->material().diffuse = GsColor::blue;
		}


		//yellow army
		for (i = 75; i < 100; i++)
		{
			_spheres->add(g = new SnGroup);
			g->separator(true); // transformations inside group do not affect outside group
			g->add(t = new SnTransform);
			g->add(m = new SnMaterial);
			g->add(sphere);
			_positions.push() = &(t->get());
			t->get().translation(p[i].x);
			m->material().diffuse = GsColor::yellow;
		}


		SnModel* sphere1 = new SnModel;

		sphere1->model()->make_sphere(GsPnt::null, 3.0f, nfaces, true);
		_spheres->add(g = new SnGroup);
		g->separator(true); // transformations inside group do not affect outside group
		g->add(t = new SnTransform);
		g->add(m = new SnMaterial);
		g->add(sphere1);
		_positions.push() = &(t->get());
		t->get().translation(p[100].x);
		m->material().diffuse = GsColor::cyan;

		SnGroup* g1;
		//	SnTransform* t1;
		SnMaterial* m1;

		SnModel* myTarget;

		myTarget = new SnModel;
		myTarget->model()->make_sphere(GsPnt(20, -25, -50), 5.0f, nfaces, true);

		_targets->add(g1 = new SnGroup);
		g1->separator(true); // transformations inside group do not affect outside group
							 //g->add(t = new SnTransform);
		g1->add(m1 = new SnMaterial);
		g1->add(myTarget);
		//_positions.push() = &(t->get());
		//	t->get().translation(p[i].x);
		m1->material().diffuse = GsColor::yellow;// rando


	}

	else if (_scenario3->value()) {
		_spheres->init();
		_positions.size(0); // fast access to later update positions
		for (i = 0; i < p.size(); i++)
		{
			_spheres->add(g = new SnGroup);
			g->separator(true); // transformations inside group do not affect outside group
			g->add(t = new SnTransform);
			g->add(m = new SnMaterial);
			g->add(sphere);
			_positions.push() = &(t->get());
			t->get().translation(p[i].x);
			m->material().diffuse = GsColor::green;
		}

	}


	else if (_scenario1->value()) {
		sphere->model()->make_sphere(GsPnt::null, 3.0f, nfaces, true);
		_spheres->init();

		_positions.size(0); 
		_spheres->add(g = new SnGroup);
		g->separator(true); // transformations inside group do not affect outside group
		g->add(t = new SnTransform);
		g->add(m = new SnMaterial);
		g->add(sphere);
		_positions.push() = &(t->get());
		t->get().translation(p[0].x);
		m->material().diffuse = GsColor::red;
		
		// fast access to later update positions
		for (i = 1; i < p.size(); i++)
		{
			//if (i == p.size() - 2)
			//	continue;
			_spheres->add(g = new SnGroup);
			g->separator(true); // transformations inside group do not affect outside group
			g->add(t = new SnTransform);
			g->add(m = new SnMaterial);
			g->add(sphere);
			_positions.push() = &(t->get());
			t->get().translation(p[i].x);
			m->material().diffuse = GsColor::green;
		}

		//SnModel* sphere3= new SnModel;;
		//sphere3->model()->make_sphere(GsPnt::null, 6.0f, nfaces, true);

		//_spheres->add(g = new SnGroup);
		//_spheres->add(g = new SnGroup);
		//g->separator(true); // transformations inside group do not affect outside group
		//g->add(t = new SnTransform);
		//g->add(m = new SnMaterial);
		//g->add(sphere3);
		//_positions.push() = &(t->get());
		//t->get().translation(p[p.size() - 2].x);
		//m->material().diffuse = GsColor::red;

	}
	
	_points->init();
	_points->visible(1);
	_points->point_size ( 3.0f );
	_points->color ( GsColor::blue );
	//for ( i=0; i<psize; i++ )
	//{
	_points->push ( p[0].x );
	//}

	_lines->init();
	_lines->color ( GsColor::gray );
	for ( i=0; i<psize; i++ )
	{
		_lines->push ( p[i].x, p[i].x+p[i].v );
	}

	_world->init();
	_world->color ( GsColor::red );
      
	int r=3;
	float fr = (float) r;
	float fr2 = fr+fr;
	const GsBox& w = psys.world();
	GsVec dx = GsVec::i*w.dx();
	GsVec dz = GsVec::k*w.dz();
	GsPnt a ( w.a.x*fr2, w.a.y, w.a.z*fr2 );
	for ( i=-r; i<=r; i++ )
	{	_world->push ( a, a+(dx*fr2) );
		a+=dz;
	}
	a.set ( w.a.x*fr2, w.a.y, w.a.z*fr2 );
	for ( i=-r; i<=r; i++ )
	{	_world->push ( a, a+(dz*fr2) );
		a+=dx;
	}
}

void MyViewer::update_scene ()
{
	const GsArray<Particle>& p = _psys->particles();
	int i, psize=p.size();
	if (_scenario1->value()) {
		_points->push(p[0].x);
	}
//for ( i=0; i<psize; i++ )
		/*{	
		_points->P[2] = p[2].x;
			_points->touch();
		}*/

	if ( _spheres->visible() )
	{	for ( i=0; i<psize; i++ )
		{	_positions[i]->setrans ( p[i].x );
		}
	}
	else
    {	for ( i=0; i<psize; i++ )
	{
		if (_scenario1) {
			_points->P[i] = p[i].x;
			_points->touch();
		}
		}
	}

	if ( _lines->visible() )
	{	_lines->init();
		for ( i=0; i<psize; i++ )
		{	_lines->push ( p[i].x, p[i].x+p[i].v );
		}
	}
}

void MyViewer::run ()
{
	if ( !_run->value() ) return; // turning sim off

	double tfac = 1.0; //ui_timeslider->value();
	double t0, tprior, tnow;

	t0 = tprior = gs_time()*tfac;
	while ( _run->value() )
	{
		// draw current state:
		update_scene ();
		ws_check();

		// check time scale:
		if ( tfac!=_tscaleslider->value() )
		{	t0 /= tfac;
			tprior /= tfac;
			tfac=_tscaleslider->value();
			t0 *= tfac;
			tprior *= tfac;
		}

		// compute next step:
		tnow = gs_time () * tfac;
		_psys->euler_step ( float(tnow-tprior) );
		tprior = tnow;

		// display some info:
		message().setf ( "run: %5.2f s", float(tnow-t0) );
	}
}

int MyViewer::uievent ( int e )
{
	switch ( e )
	{	case EvInit:
		{	_psys->init ( _psys->last_cfg_file() );
			build_scene ( *_psys, _nfaces );
		} break;

		case EvSeek:
		{	
			_psys->seek1(_seek->value());
			
			/*float windmag = _windslider->value();
			if ( !_wind->value() ) windmag=0;
			_psys->external_force ( GsVec( windmag, 0, 0 ) );
	*/	} break;


		case EvSeek1:
		{
			_psys->seek1(_seek1->value());

			/*float windmag = _windslider->value();
			if ( !_wind->value() ) windmag=0;
			_psys->external_force ( GsVec( windmag, 0, 0 ) );
			*/	} break;

		case EvFlee:
		{
			_psys->flee1(_flee->value());

			/*float windmag = _windslider->value();
			if ( !_wind->value() ) windmag=0;
			_psys->external_force ( GsVec( windmag, 0, 0 ) );
			*/	} break;



		case EvAttack:
		{
			_psys->attack1(_attack->value());

			/*float windmag = _windslider->value();
			if ( !_wind->value() ) windmag=0;
			_psys->external_force ( GsVec( windmag, 0, 0 ) );
			*/	} break;

		case EvGather:
		{
			_psys->gather1(_gather->value());

			/*float windmag = _windslider->value();
			if ( !_wind->value() ) windmag=0;
			_psys->external_force ( GsVec( windmag, 0, 0 ) );
			*/	} break;


		case EvPersue:
		{
			_psys->persue1(_persue->value());

			/*float windmag = _windslider->value();
			if ( !_wind->value() ) windmag=0;
			_psys->external_force ( GsVec( windmag, 0, 0 ) );
			*/	} break;

		case EvPersue2:
		{
			_psys->persue21(_persue2->value());

			/*float windmag = _windslider->value();
			if ( !_wind->value() ) windmag=0;
			_psys->external_force ( GsVec( windmag, 0, 0 ) );
			*/	} break;

		case EvScen1:
		{


			_psys->scene1_(_scenario1->value());

			_psys->scene2_(false);
			_scenario2->value(false);

			_psys->scene3_(false);
			_scenario3->value(false);

			/*_psys->scene2_(_scenario2->value());
			_psys->scene3_(_scenario3->value());*/

		/*	_psys->init("../src/config.txt");
			build_scene(*_psys, _nfaces);*/
			_psys->init("../src/config.txt");
			build_scene(*_psys, _nfaces); 

			/*float windmag = _windslider->value();
			if ( !_wind->value() ) windmag=0;
			_psys->external_force ( GsVec( windmag, 0, 0 ) );
			*/	} break;

		case EvScen2:
		{
			
			
			_psys->scene2_(_scenario2->value());
		
		

			_psys->scene1_(false);
			_scenario1->value(false);

			_psys->scene3_(false);
			_scenario3->value(false);

			_psys->init("../src/config.txt");
			build_scene(*_psys, _nfaces);
			/*_psys->init(_psys->last_cfg_file());
			build_scene(*_psys, _nfaces);*/

			/*float windmag = _windslider->value();
			if ( !_wind->value() ) windmag=0;
			_psys->external_force ( GsVec( windmag, 0, 0 ) );
			*/	} break;

		case EvScen3:
		{
			_psys->scene3_(_scenario3->value());


		

			_psys->scene1_(false);
			_scenario1->value(false);

			_psys->scene2_(false);
			_scenario2->value(false);

			_psys->init("../src/config.txt");
			build_scene(*_psys, _nfaces);

			/*_psys->init(_psys->last_cfg_file());
			build_scene(*_psys, _nfaces);*/

			/*float windmag = _windslider->value();
			if ( !_wind->value() ) windmag=0;
			_psys->external_force ( GsVec( windmag, 0, 0 ) );
			*/	} break;

		case EvBounce:
		{	_psys->bounce ( _bounce->value() );
		} break;

		case EvSCollision:
		{	_psys->spring_collision_prevention ( _scol->value() );
		} break;

		case EvVCollision:
		{	_psys->velocity_collision_prevention ( _vcol->value() );
		} break;

		case EvCRestitut:
		{	_psys->coeff_restitution ( _crestslider->value() );
		} break;

		case EvView:
		{	view ( _vvel->value(), _vworld->value(), _vsphere->value() );
		} break;

		case EvRun: run(); break;

		case EvExit: gs_exit();
	}
	return WsViewer::uievent(e);
}

int MyViewer::handle_scene_event ( const GsEvent &e )
{
	if ( e.button1 )
	{	// nothing here for now
	}

	return WsViewer::handle_scene_event ( e );
}
