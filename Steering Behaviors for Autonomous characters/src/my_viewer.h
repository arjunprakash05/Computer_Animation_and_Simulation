# pragma once

# include <sig/sn_group.h>
# include <sig/sn_points.h>
# include <sig/sn_lines.h>
# include <sigogl/ui_radio_button.h>
# include <sigogl/ui_slider.h>
# include <sigogl/ui_button.h>
# include <sigogl/ui_check_button.h>
# include <sigogl/ws_viewer.h>

# include "particle_system.h"

class MyViewer : public WsViewer
 { public: // scene and other data:
	SnGroup*  _root;
	SnGroup*  _spheres;
	SnPoints* _points;
	SnLines* _lines;
	SnLines* _world;
	GsArray<GsMat*> _positions;
	float _sphereradius;
	ParticleSystem* _psys;
	int _nfaces;
	SnGroup* _targets;

   public: // ui:
	UiButton* _init;
	UiCheckButton* _run;
	UiCheckButton* _seek;
	UiCheckButton* _seek1;
	UiCheckButton* _flee;

	UiCheckButton* _persue;
	UiCheckButton* _persue2;

	UiCheckButton* _attack;
	UiCheckButton* _gather;

	UiCheckButton* _scenario1;
	UiCheckButton* _scenario2;
	UiCheckButton* _scenario3;


	UiCheckButton* _scol;
	UiCheckButton* _vcol;
	UiCheckButton* _bounce;
	UiSlider* _windslider;
	UiSlider* _tscaleslider;
	UiSlider* _crestslider;
	UiCheckButton* _vvel;
	UiCheckButton* _vworld;
	UiCheckButton* _vsphere;

   public:
	MyViewer ( int x, int y, int w, int h, const char *l=0 );
   ~MyViewer ();

	void build_ui ();
	void sphere_radius ( float r ) { _sphereradius=r; }

	void view ( bool vel, bool world, bool spheres );
	void build_scene ( ParticleSystem& psys, int nfaces );
	void update_scene ();

	void run ();

   public :
	virtual int handle_scene_event ( const GsEvent &e );
	virtual int uievent ( int e );
};

