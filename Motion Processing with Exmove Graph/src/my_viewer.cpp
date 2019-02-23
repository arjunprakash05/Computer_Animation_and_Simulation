
# include "my_viewer.h"

# include <sigogl/ui_button.h>
# include <sigogl/ui_radio_button.h>
# include <sig/sn_primitive.h>
# include <sig/sn_transform.h>
# include <sig/sn_manipulator.h>
# include <sig/sn_material.h>

# include <sigogl/ws_run.h>

MyViewer::MyViewer ( int x, int y, int w, int h, const char* l ) : WsViewer(x,y,w,h,l)
{
	_blendbut=_followbut=0;
	_animating=false;
	_lastkey=0;
	build_ui ();
	ObstructionA = new SnGroup;
	ObstructionB = new SnGroup;
	ObstructionC = new SnGroup;
	ObstructionD = new SnGroup; 
	ObstructionE = new SnGroup;
	ObstructionF = new SnGroup;
	ObstructionH = new SnGroup;
	ObstructionG = new SnGroup; 
	ObstructionI = new SnGroup;
	ObstructionJ = new SnGroup;
	ObstructionK = new SnGroup;
	ObstructionL = new SnGroup;
	Obstructionnew = new SnGroup;

	C1 = new SnGroup;
	C2 = new SnGroup;
	_traversal = new SnPoints;
	
}

void MyViewer::build_ui ()
{
	UiPanel *p, *sp;
	UiManager* uim = WsWindow::uim();
	p = uim->add_panel ( "", UiPanel::HorizLeft );
	p->add ( new UiButton ( "Options", sp=new UiPanel() ) );
	{	UiPanel* p=sp;
		p->add ( _blendbut=new UiCheckButton ( "Blend", EvBlend ) ); 
		p->add ( _followbut=new UiCheckButton ( "Follow", EvFollow ) ); 
	}
	p->add ( new UiButton ( "Exit", EvExit ) ); p->top()->separate();
}

void MyViewer::build_scene ( KnSkeleton* sk, bool addfloor )
{
	if ( addfloor )
	{	// Let's add a ground floor:
		GsPrimitive floor;
		floor.box(700.0f,1.0f,700.0f); floor.center.y=-1.0f;
		floor.material.diffuse=GsColor::red;
		SnModel* ground = new SnModel;
		ground->model()->make_primitive ( floor );
		rootg()->add ( ground );


	}
	//right bar
	GsPrimitive floor1;
	floor1.box(5.0f, 20.0f, 250.0f);
	floor1.center.y = 10.0f;
	floor1.center.x = 500.0f;
	floor1.center.z = -100.0f;
	floor1.material.diffuse = GsColor::darkblue;
	SnModel* ground1 = new SnModel;
	ground1->model()->make_primitive(floor1);
	rootg()->add(ground1);

	//left bar
	GsPrimitive floor2;
	floor2.box(5.0f, 20.0f, 250.0f);
	floor2.center.y = 10.0f;
	floor2.center.x = -500.0f;
	floor2.center.z = -100.0f;
	floor2.material.diffuse = GsColor::darkblue;
	SnModel* ground2 = new SnModel;
	ground2->model()->make_primitive(floor2);
	rootg()->add(ground2);

	//boxes within large cuboids:: on the right
	GsPrimitive floor2a;
	floor2a.box(4.0f, 20.0f, 50.0f);
	floor2a.center.y = 10.0f;
	floor2a.center.x = -500.0f;
	floor2a.center.z = -100.0f;
	floor2a.material.diffuse = GsColor::darkblue;
	SnModel* ground2a = new SnModel;
	ground2a->model()->make_primitive(floor2a);
	rootg()->add(ground2a);

	GsPrimitive floor2b;
	floor2b.box(4.0f, 20.0f, 50.0f);
	floor2b.center.y = 10.0f;
	floor2b.center.x = -500.0f;
	floor2b.center.z = -200.0f;
	floor2b.material.diffuse = GsColor::darkblue;
	SnModel* ground2b = new SnModel;
	ground2b->model()->make_primitive(floor2b);
	rootg()->add(ground2b);

	GsPrimitive floor2c;
	floor2c.box(4.0f, 20.0f, 50.0f);
	floor2c.center.y = 10.0f;
	floor2c.center.x = -500.0f;
	floor2c.center.z = -300.0f;
	floor2c.material.diffuse = GsColor::darkblue;
	SnModel* ground2c = new SnModel;
	ground2c->model()->make_primitive(floor2c);
	rootg()->add(ground2c);

	GsPrimitive floor2d;
	floor2d.box(4.0f, 20.0f, 50.0f);
	floor2d.center.y = 10.0f;
	floor2d.center.x = -500.0f;
	floor2d.center.z = 0.0f;
	floor2d.material.diffuse = GsColor::darkblue;
	SnModel* ground2d = new SnModel;
	ground2d->model()->make_primitive(floor2d);
	rootg()->add(ground2d);

	GsPrimitive floor2e;
	floor2e.box(4.0f, 20.0f, 50.0f);
	floor2e.center.y = 10.0f;
	floor2e.center.x = -500.0f;
	floor2e.center.z = 100.0f;
	floor2e.material.diffuse = GsColor::darkblue;
	SnModel* ground2e = new SnModel;
	ground2e->model()->make_primitive(floor2e);
	rootg()->add(ground2e);


	//boxes within large cuboids:: on the right
	GsPrimitive floor1a;
	floor1a.box(4.0f, 20.0f, 50.0f);
	floor1a.center.y = 10.0f;
	floor1a.center.x = 500.0f;
	floor1a.center.z = -100.0f;
	floor1a.material.diffuse = GsColor::darkblue;
	SnModel* ground1a = new SnModel;
	ground1a->model()->make_primitive(floor1a);
	rootg()->add(ground1a);

	GsPrimitive floor1b;
	floor1b.box(4.0f, 20.0f, 50.0f);
	floor1b.center.y = 10.0f;
	floor1b.center.x = 500.0f;
	floor1b.center.z = -200.0f;
	floor1b.material.diffuse = GsColor::darkblue;
	SnModel* ground1b = new SnModel;
	ground1b->model()->make_primitive(floor1b);
	rootg()->add(ground1b);

	GsPrimitive floor1c;
	floor1c.box(4.0f, 20.0f, 50.0f);
	floor1c.center.y = 10.0f;
	floor1c.center.x = 500.0f;
	floor1c.center.z = -300.0f;
	floor1c.material.diffuse = GsColor::darkblue;
	SnModel* ground1c = new SnModel;
	ground1c->model()->make_primitive(floor1c);
	rootg()->add(ground1c);

	GsPrimitive floor1d;
	floor1d.box(4.0f, 20.0f, 50.0f);
	floor1d.center.y = 10.0f;
	floor1d.center.x = 500.0f;
	floor1d.center.z = 0.0f;
	floor1d.material.diffuse = GsColor::darkblue;
	SnModel* ground1d = new SnModel;
	ground1d->model()->make_primitive(floor1d);
	rootg()->add(ground1d);

	GsPrimitive floor1e;
	floor1e.box(4.0f, 20.0f, 50.0f);
	floor1e.center.y = 10.0f;
	floor1e.center.x = 500.0f;
	floor1e.center.z = 100.0f;
	floor1e.material.diffuse = GsColor::darkblue;
	SnModel* ground1e = new SnModel;
	ground1e->model()->make_primitive(floor1e);
	rootg()->add(ground1e);


	//box for collision
	GsPrimitive box1;
	box1.box(25.0f, 25.0f, 25.0f);
	box1.center.y = 15.0f;
	box1.center.x = 300.0f;
	box1.center.z = 240.0f;
	box1.material.diffuse = GsColor::darkblue;
	SnModel* Box1 = new SnModel;
	Box1->model()->make_primitive(box1);
	rootg()->add(Box1);

	//box2 for collision
	GsPrimitive box2;
	box2.box(25.0f, 25.0f, 25.0f);
	box2.center.y = 15.0f;
	box2.center.x = -300.0f;
	box2.center.z = -480.0f;
	box2.material.diffuse = GsColor::darkblue;
	SnModel* Box2 = new SnModel;
	Box2->model()->make_primitive(box2);
	rootg()->add(Box2);

	//box3 for collision
	GsPrimitive box3;
	box3.box(25.0f, 25.0f, 25.0f);
	box3.center.y = 15.0f;
	box3.center.x = 300.0f;
	box3.center.z = -480.0f;
	box3.material.diffuse = GsColor::darkblue;
	SnModel* Box3 = new SnModel;
	Box3->model()->make_primitive(box3);
	rootg()->add(Box3);

	//box4 for collision
	GsPrimitive box4;
	box4.box(25.0f, 25.0f, 25.0f);
	box4.center.y = 15.0f;
	box4.center.x = -300.0f;
	box4.center.z = 240.0f;
	box4.material.diffuse = GsColor::darkblue;
	SnModel* Box4 = new SnModel;
	Box4->model()->make_primitive(box4);
	rootg()->add(Box4);


	rootg()->add(ObstructionA);
	rootg()->add(ObstructionB);
	rootg()->add(ObstructionC);
	rootg()->add(ObstructionD);
	rootg()->add(ObstructionE);
	rootg()->add(ObstructionF);
	rootg()->add(ObstructionG);
	rootg()->add(ObstructionH);
	rootg()->add(ObstructionI);
	rootg()->add(ObstructionJ);
	rootg()->add(ObstructionK);
	rootg()->add(ObstructionL);
	rootg()->add(Obstructionnew);
	rootg()->add(C1);
	rootg()->add(C2);

	rootg()->add(_traversal);

	_traversal->init();
	_traversal->point_size(3.0f);
	_traversal->color(GsColor::yellow);


	// Create a skeleton scene node:
	_kns = new KnScene;
	_kns->connect ( sk );
	_kns->set_visibility ( 0, 0, 1, 0, 0 );
	rootg()->add ( _kns );

	ObstructionA->visible();
	ObstructionB->visible();
	ObstructionC->visible();
	ObstructionD->visible();
	ObstructionE->visible();
	ObstructionF->visible();
	ObstructionG->visible();
	ObstructionH->visible();
	ObstructionI->visible();
	ObstructionJ->visible();
	ObstructionK->visible();
	ObstructionL->visible();
	Obstructionnew->visible();
	C1->visible();
	C2->visible();

	/*
	SnModel* c1model = new SnModel;
	c1model->model()->make_cylinder(GsPnt(100.0, 10.0, 200.0), GsPnt(0.0, 10.0, -200.0), 0.1f, 0.1f,10,1);
	//c1model->model()->make_tube(GsPnt(100.0, 10.0, 200.0), GsPnt(0.0, 10.0, -200.0), 0.1f, 0.1f, 10, 1);
	SnGroup* gobsnewc1;
	SnTransform* tobsnewc1;
	SnMaterial* mobsnewc1;
	C1->init();
	{
	C1->add(gobsnewc1 = new SnGroup);
	gobsnewc1->separator(true); // transformations inside group do not affect outside group
	gobsnewc1->add(tobsnewc1 = new SnTransform);
	gobsnewc1->add(mobsnewc1 = new SnMaterial);
	gobsnewc1->add(c1model);
	mobsnewc1->material().diffuse = GsColor::brown;
	}*./

	/*SnModel* c2model = new SnModel;
	c2model->model()->make_sphere(GsPnt(300.0, 10.0, 0.0), 20, 10, true);
	SnGroup* gobsnewc2;
	SnTransform* tobsnewc2;
	SnMaterial* mobsnewc2;
	C2->init();
	{
	C2->add(gobsnewc2 = new SnGroup);
	gobsnewc2->separator(true); // transformations inside group do not affect outside group
	gobsnewc2->add(tobsnewc2 = new SnTransform);
	gobsnewc2->add(mobsnewc2 = new SnMaterial);
	gobsnewc2->add(c2model);
	mobsnewc2->material().diffuse = GsColor::brown;
	}*/
	/*
	SnModel* ObsModelnew = new SnModel;
	ObsModelnew->model()->make_sphere(GsPnt(0.0, 10.0, -240.0), 20, 10, true);
	SnGroup* gobsnew;
	SnTransform* tobsnew;
	SnMaterial* mobsnew;
	Obstructionnew->init();
	{
		Obstructionnew->add(gobsnew = new SnGroup);
		gobsnew->separator(true); // transformations inside group do not affect outside group
		gobsnew->add(tobsnew = new SnTransform);
		gobsnew->add(mobsnew = new SnMaterial);
		gobsnew->add(ObsModelnew);
		mobsnew->material().diffuse = GsColor::cyan;
	}*/


	SnModel* ObsModelA = new SnModel;
	ObsModelA->model()->make_sphere(GsPnt(0.0, 10.0, -360.0), 20, 10, true);
	SnGroup* gobs1;
	SnTransform* tobs1;
	SnMaterial* mobs1;
	ObstructionA->init();
	{
		ObstructionA->add(gobs1 = new SnGroup);
		gobs1->separator(true); // transformations inside group do not affect outside group
		gobs1->add(tobs1 = new SnTransform);
		gobs1->add(mobs1 = new SnMaterial);
		gobs1->add(ObsModelA);
		mobs1->material().diffuse = GsColor::green;
	}

	SnModel* ObsModelB = new SnModel;
	ObsModelB->model()->make_sphere(GsPnt(0.0, 10.0, 120.0), 20, 10, true);
	SnGroup* gobs2;
	SnTransform* tobs2;
	SnMaterial* mobs2;
	ObstructionB->init();
	{
		ObstructionB->add(gobs2 = new SnGroup);
		gobs2->separator(true); // transformations inside group do not affect outside group
		gobs2->add(tobs2 = new SnTransform);
		gobs2->add(mobs2 = new SnMaterial);
		gobs2->add(ObsModelB);
		mobs2->material().diffuse = GsColor::green;
	}

	SnModel* ObsModelC = new SnModel;
	ObsModelC->model()->make_sphere(GsPnt(240.0, 10.0, -120.0), 20, 10, true);
	SnGroup* gobs3;
	SnTransform* tobs3;
	SnMaterial* mobs3;
	ObstructionC->init();
	{
		ObstructionC->add(gobs3 = new SnGroup);
		gobs3->separator(true); // transformations inside group do not affect outside group
		gobs3->add(tobs3 = new SnTransform);
		gobs3->add(mobs3 = new SnMaterial);
		gobs3->add(ObsModelC);
		mobs3->material().diffuse = GsColor::green;
	}

	SnModel* ObsModelD = new SnModel;
	ObsModelD->model()->make_sphere(GsPnt(-240.0, 10.0, -120.0), 20, 10, true);
	SnGroup* gobs4;
	SnTransform* tobs4;
	SnMaterial* mobs4;
	ObstructionD->init();
	{
		ObstructionD->add(gobs4 = new SnGroup);
		gobs4->separator(true); // transformations inside group do not affect outside group
		gobs4->add(tobs4 = new SnTransform);
		gobs4->add(mobs4 = new SnMaterial);
		gobs4->add(ObsModelD);
		mobs4->material().diffuse = GsColor::green;
	}

	SnModel* ObsModelE = new SnModel;
	ObsModelE->model()->make_sphere(GsPnt(120.0, 10.0, -240.0), 20, 10, true);
	SnGroup* gobs5;
	SnTransform* tobs5;
	SnMaterial* mobs5;
	ObstructionE->init();
	{
		ObstructionE->add(gobs5 = new SnGroup);
		gobs5->separator(true); // transformations inside group do not affect outside group
		gobs5->add(tobs5 = new SnTransform);
		gobs5->add(mobs5 = new SnMaterial);
		gobs5->add(ObsModelE);
		mobs5->material().diffuse = GsColor::black;
	}

	SnModel* ObsModelF = new SnModel;
	ObsModelF->model()->make_sphere(GsPnt(-120.0, 10.0, -240.0), 20, 10, true);
	SnGroup* gobs6;
	SnTransform* tobs6;
	SnMaterial* mobs6;
	ObstructionF->init();
	{
		ObstructionF->add(gobs6 = new SnGroup);
		gobs6->separator(true); // transformations inside group do not affect outside group
		gobs6->add(tobs6 = new SnTransform);
		gobs6->add(mobs6 = new SnMaterial);
		gobs6->add(ObsModelF);
		mobs6->material().diffuse = GsColor::black;
	}

	SnModel* ObsModelG = new SnModel;
	ObsModelG->model()->make_sphere(GsPnt(120.0, 10.0, 0.0), 20, 10, true);
	SnGroup* gobs7;
	SnTransform* tobs7;
	SnMaterial* mobs7;
	ObstructionG->init();
	{
		ObstructionG->add(gobs7 = new SnGroup);
		gobs7->separator(true); // transformations inside group do not affect outside group
		gobs7->add(tobs7 = new SnTransform);
		gobs7->add(mobs7 = new SnMaterial);
		gobs7->add(ObsModelG);
		mobs7->material().diffuse = GsColor::black;
	}

	SnModel* ObsModelH = new SnModel;
	ObsModelH->model()->make_sphere(GsPnt(-120.0, 10.0, 0.0), 20, 10, true);
	SnGroup* gobs8;
	SnTransform* tobs8;
	SnMaterial* mobs8;
	ObstructionH->init();
	{
		ObstructionH->add(gobs8 = new SnGroup);
		gobs8->separator(true); // transformations inside group do not affect outside group
		gobs8->add(tobs8 = new SnTransform);
		gobs8->add(mobs8 = new SnMaterial);
		gobs8->add(ObsModelH);
		mobs8->material().diffuse = GsColor::black;
	}



	SnModel* ObsModelI = new SnModel;
	ObsModelI->model()->make_sphere(GsPnt(320.0, 10.0, -120.0), 20, 10, true);
	SnGroup* gobs9;
	SnTransform* tobs9;
	SnMaterial* mobs9;
	ObstructionI->init();
	{
		ObstructionI->add(gobs9 = new SnGroup);
		gobs9->separator(true); // transformations inside group do not affect outside group
		gobs9->add(tobs9 = new SnTransform);
		gobs9->add(mobs9 = new SnMaterial);
		gobs9->add(ObsModelI);
		mobs9->material().diffuse = GsColor::darkgreen;
	}

	SnModel* ObsModelJ = new SnModel;
	ObsModelJ->model()->make_sphere(GsPnt(-320.0, 10.0, -120.0), 20, 10, true);
	SnGroup* gobs10;
	SnTransform* tobs10;
	SnMaterial* mobs10;
	ObstructionJ->init();
	{
		ObstructionJ->add(gobs10 = new SnGroup);
		gobs10->separator(true); // transformations inside group do not affect outside group
		gobs10->add(tobs10 = new SnTransform);
		gobs10->add(mobs10 = new SnMaterial);
		gobs10->add(ObsModelJ);
		mobs10->material().diffuse = GsColor::darkgreen;
	}

	SnModel* ObsModelK = new SnModel;
	ObsModelK->model()->make_sphere(GsPnt(0.0, 10.0, -440.0), 20, 10, true);
	SnGroup* gobs11;
	SnTransform* tobs11;
	SnMaterial* mobs11;
	ObstructionK->init();
	{
		ObstructionK->add(gobs11 = new SnGroup);
		gobs11->separator(true); // transformations inside group do not affect outside group
		gobs11->add(tobs11 = new SnTransform);
		gobs11->add(mobs11 = new SnMaterial);
		gobs11->add(ObsModelK);
		mobs11->material().diffuse = GsColor::darkgreen;
	}

	SnModel* ObsModelL = new SnModel;
	ObsModelL->model()->make_sphere(GsPnt(0.0, 10.0, 200.0), 20, 10, true);
	SnGroup* gobs12;
	SnTransform* tobs12;
	SnMaterial* mobs12;
	ObstructionL->init();
	{
		ObstructionL->add(gobs12 = new SnGroup);
		gobs12->separator(true); // transformations inside group do not affect outside group
		gobs12->add(tobs12 = new SnTransform);
		gobs12->add(mobs12 = new SnMaterial);
		gobs12->add(ObsModelL);
		mobs12->material().diffuse = GsColor::darkgreen;
	}

}

int MyViewer::handle_keyboard ( const GsEvent &e )
{
	int ret = WsViewer::handle_keyboard ( e ); // 1st let system check events
	if ( ret ) return ret;

	_lastkey = e.key;
	//gsout<<"Key pressed: "<<e.key<<gsnl;

	switch ( e.key )
	{	case GsEvent::KeyEsc : gs_exit(); return 1;
	}

	return 0;
}

int MyViewer::uievent ( int e )
{
	switch ( e )
	{	case EvBlend: break;
		case EvFollow: break;
		case EvExit: gs_exit();
	}
	return WsViewer::uievent(e);
}
