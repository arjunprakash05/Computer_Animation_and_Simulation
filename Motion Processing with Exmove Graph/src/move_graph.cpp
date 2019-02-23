
# include "move_graph.h"

MoveGraph::MoveGraph ()
{
}

static KnMotion* load_motion ( KnSkeleton* sk, const char* filename )
{
	KnMotion* m = new KnMotion;
	if ( !m->load ( filename ) ) gsout.fatal("Error loading [%s]!",filename);
	m->connect ( sk );
	m->ref ();
	return m;
}

void MoveGraph::init ( KnSkeleton* sk )
{
	nodes.push()->motion = load_motion ( sk, "../data/idle_stand.bvh" ); // 0
	nodes.push()->motion = load_motion ( sk, "../data/stand2right_step.bvh" ); // 1
	nodes.push()->motion = load_motion ( sk, "../data/right_step.bvh" ); // 2
	nodes.push()->motion = load_motion ( sk, "../data/left_step.bvh" ); // 3
	nodes.push()->motion = load_motion ( sk, "../data/right_step2stand.bvh" ); // 4
	nodes.push()->motion = load_motion ( sk, "../data/turn180.bvh" ); // 5
	nodes.push()->motion = load_motion ( sk, "../data/turn180.bvh"); // 6
	nodes.push()->motion = load_motion ( sk, "../data/turn180_mirror.bvh"); // 7
	nodes.push()->motion = load_motion ( sk, "../data/turn180_mirror.bvh"); // 8
	nodes.push()->motion = load_motion ( sk, "../data/turn180.bvh"); // 9
	nodes.push()->motion = load_motion ( sk, "../data/run2stand_rightstep.bvh"); // 10 ready to run1
	nodes.push()->motion = load_motion ( sk, "../data/run2stand_leftstep.bvh"); // 11 ready to run2
	nodes.push()->motion = load_motion ( sk, "../data/run_rightstep.bvh"); // 12 run1
	nodes.push()->motion = load_motion ( sk, "../data/run_leftstep.bvh"); // 13 //run2
	nodes.push()->motion = load_motion ( sk, "../data/turn180 -run.bvh"); // 14 //turn while run
	nodes.push()->motion = load_motion ( sk, "../data/turn180_mirror - run.bvh"); // 15
	nodes.push()->motion = load_motion ( sk, "../data/turn180_mirror.bvh"); // 16 //collision detection

	Node* n;
	Transition* t;

	// motion node 0: //stop
		n=nodes[0]; n->nextnode=0;
		n->anytimetransitions=true;
		t=&n->trans.push(); t->key='w'; t->nextnode=1; 
		t = &n->trans.push(); t->key = 65361; t->nextnode = 6;
		t = &n->trans.push(); t->key = 65363; t->nextnode = 7;
		t = &n->trans.push(); t->key = 65362; t->nextnode = 1;
		t = &n->trans.push(); t->key = 65364; t->nextnode = 4;
	
	// motion node 1: stand to walk
		n = nodes[1]; n->nextnode = 2;
		n->anytimetransitions = false;

	// motion node 2:
		n = nodes[2]; n->nextnode = 3;
		n->anytimetransitions = false;
		t = &n->trans.push(); t->key = 't'; t->nextnode = 5;
		t = &n->trans.push(); t->key = 's'; t->nextnode = 0;
		t = &n->trans.push(); t->key = 'r'; t->nextnode = 12;
		t = &n->trans.push(); t->key = 65361; t->nextnode = 6;  //left 180
		//t = &n->trans.push(); t->key = 'r'; t->nextnode = 12;
		//t = &n->trans.push(); t->key = 65361; t->nextnode = 6;  //left 180
		t = &n->trans.push(); t->key = 65362; t->nextnode = 1;
		t = &n->trans.push(); t->key = 65364; t->nextnode = 4;

	// motion node 3:
		n = nodes[3]; n->nextnode = 2;
		n->anytimetransitions = false;
		t = &n->trans.push(); t->key = 's'; t->nextnode = 0;
		t = &n->trans.push(); t->key = 65363; t->nextnode = 7;// left 180 mirror
		t = &n->trans.push(); t->key = 'm'; t->nextnode = 8;
		t = &n->trans.push(); t->key = 'n'; t->nextnode = 9;

	// motion node 4:
		n = nodes[4]; n->nextnode = 5;
		n->anytimetransitions = false;

	// motion node 5: full turn 180 degrees
		n = nodes[5]; n->nextnode = 3;
		n->anytimetransitions = false;
		t = &n->trans.push(); t->key = 's'; t->nextnode = 0;

	// motion node 6:
		n = nodes[6]; n->nextnode = 2;
		n->anytimetransitions = false;
		t = &n->trans.push(); t->key = 'w'; t->nextnode = 2;
		t = &n->trans.push(); t->key = 65363; t->nextnode = 7;

	// motion node 7:
		n = nodes[7]; n->nextnode = 3;
		n->anytimetransitions = false;
		t = &n->trans.push(); t->key = 'w'; t->nextnode = 3;
		t = &n->trans.push(); t->key = 65361; t->nextnode = 6;
	
	// motion node 8:
		n = nodes[8]; n->nextnode = 2;
	
	// motion node 9:
		n = nodes[9]; n->nextnode = 2;
		n->anytimetransitions = false;

	// motion node 10:
		n = nodes[10]; n->nextnode = 12;
		n->anytimetransitions = false;
		t = &n->trans.push(); t->key = 65361; t->nextnode = 14;
		t = &n->trans.push(); t->key = 65363; t->nextnode = 15;

	// motion node 12:
		n = nodes[12]; n->nextnode = 13;
		n->anytimetransitions = false;
		t = &n->trans.push(); t->key = 65361; t->nextnode = 14;  //left 180
		t = &n->trans.push(); t->key = 65363; t->nextnode = 15;  //left 180

	//// motion node 12:
	//	n = nodes[12]; n->nextnode = 13;
	//	n->anytimetransitions = false;
	//	t = &n->trans.push(); t->key = 65361; t->nextnode = 14;  //left 180
	//	t = &n->trans.push(); t->key = 65363; t->nextnode = 15;  //left 180
	
	// motion node 13:
		n = nodes[13]; n->nextnode = 12;
		t = &n->trans.push(); t->key = 's'; t->nextnode = 0;
	
	// motion node 14:
		n = nodes[14]; n->nextnode = 12;
	
	// motion node 15:
		n = nodes[15]; n->nextnode = 12;

	// motion node 16:
		n = nodes[16]; n->nextnode = 2;
		n->anytimetransitions = false;
		t = &n->trans.push(); t->key = 't'; t->nextnode = 5;
		t = &n->trans.push(); t->key = 's'; t->nextnode = 0;
		t = &n->trans.push(); t->key = 'w'; t->nextnode = 3;
		t = &n->trans.push(); t->key = 'r'; t->nextnode = 12;
		t = &n->trans.push(); t->key = 65361; t->nextnode = 6;
		t = &n->trans.push(); t->key = 65362; t->nextnode = 1;
		t = &n->trans.push(); t->key = 65364; t->nextnode = 4;
		//t = &n->trans.push(); t->key = 'm'; t->nextnode = 0;
		//t = &n->trans.push(); t->key = 'n'; t->nextnode = 6;

}
