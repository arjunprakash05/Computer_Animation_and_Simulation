# pragma once

# include <sig/gs_event.h>
# include <sig/gs_array.h>
# include <sigkin/kn_motion.h>
# include <sigkin/kn_skeleton.h>

// Simple class to manage a move graph
class MoveGraph
{
   public:
	struct Transition
	{	int key; // pressing this key will trigger transition
		int nextnode; // will transition to this node
	};

	struct Node
	{	KnMotion* motion; // motion of this node
		GsArray<Transition> trans; // user-selectable transitions
		bool anytimetransitions;
		int nextnode; // the next motion may self-concatenate or be a new one
		Node () { motion=0; nextnode=0; }
	   ~Node () { if(motion) motion->unref(); }
	};

	GsArrayPt<Node> nodes; // info for each move graph node

   public :
	MoveGraph ();
	void init ( KnSkeleton* sk );
};

