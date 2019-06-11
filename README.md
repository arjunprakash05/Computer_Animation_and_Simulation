# Computer Animation and Simulation Coding Assignments:
## All projects developed using Object Oriented Programming concepts.

## 1) Motion Processing with ExMoveGraph
### Introduction
MoveGraph with Keyboard Control
In this Project, a skeleton (character) made up of many joints
has been used to examine the concatenation of motion processing.
The main goal was to make the character move across the
obstacles placed on the floor in a perfect manner. Objects of
different shapes and sizes are placed on the floor as seen in Figure
To move the character, the keyboard keys have been used.
Experiments with Blending function have also been done in order
to make the transition between the motions in a smooth manner
and prevent jerks during the change of states.

### Design and Methodology
The Exmovegraph source code has been used to
implement the motion graph algorithm. Initially, an in-depth
study of the source code was done to understand the motion
processing. To add new motions to the graph, .bvh files have
been added such as turn180_mirror.bvh. To change the
direction in which the character is moving and to achieve the
required angle of rotation, the duration of the motion has been
reduced so that the character does not complete the total 180-
degree rotation. This also helps in modifying the global root
rotation. Additionally, to make the character not collide with
the objects placed in the motion path, Collision Detection is
done by calculating the distance between the object and the
current position vector of the character. The collision detection
is implemented only on some primitive in the project. The 4
boxes on the corners and the 2 long bars were able to detect
the character and make it move in the opposite direction.

### Implementation challenges
During the implementation of the algorithm, a number of
challenges were seen that were not trivial to solve. Some such
challenges will be discussed in this section. Firstly, as soon as
the character changes its state i.e. on pressing a key, the
updated motion takes some time to activate it-self which
eventually causes a delay in the motion graph. Due to this
delay in activation of new state, motions were not being
implemented immediately at the press of a key as seen in
figure 2. Secondly, during the collision detection, sometimes
the character tends to go inside an infinite loop which makes it
to revolve around the detected object which can be seen in
Figure 4 (Box placed in down right corner). Although this
challenge is rarely seen, it was interesting to visualize it.

### Result and Evaluations of the Proposed Solution
To solve the challenges discussed in the previous section,
few strategies were used to solve them. To resolve the issue of
the motion being implemented after few seconds, various
things were tested. The distance travelled by the character
after pressing the key was reduced by some specific amount so
that the character covers less distance before it rotates by the
required angle. Also, to solve the turning problem, motion was
initiated at some frames ahead of the start motion and then that
specific motion was applied at a small interval before the local
time i.e. the previous local time (local time = local time - small
interval). This helped to resolve the issue as seen in Figure 3.
Furthermore, to solve that challenge that was seen in the
collision detection was partially solved by changing the
position vector of the object. Rather than specifying the center
point of the object, the coordinates of the edges of the object
were calculated and set as the collision detection point. This
helped to partially solve the challenges. After fixing the issue
in Collision Detection, perfect results can be achieved as seen
in figure 5. However, sometimes Collision detection does not
work correctly while playing with the move graph.
Furthermore, to optimize blending or to minimize the jerk at
change of motion, variations were done to the blending
window. It was seen that as the Blending window value was
increased, the character behaved in a more rigid manner
reducing the smoothness of the motion processing. Further
evaluating the proposed solution, it is seen that the character is
able to pass even through the narrow spaces only when the key
is clicked at the right time.

### Conclusion
In this project, various new topics were studied and
evaluated. The results and figures show that the character is
able to move across the obstacles in a smooth manner
although some mis behavior is seen few times.


## 2) Particle based Cloth Simulation
### Numerical Solvers Implemented
In this Project, a particle based cloth simulation has been animated. Two different solvers (Euler Method and Mid-Point Method) have been used to calculate the change of positions of each particle and constraints on the particles system.
a) Euler Method: This method uses the derivative information to make a linear prediction about the value at the next desired time. However, the approximations could be inaccurate as in this method each value is not predicted due to the step size. It resembles as creating a sequence of straight line segments.
b) Mid-Point (improved Euler method): This Solver provides better results as it requires working out the Taylor series approximation (one additional term). The input of the midpoint is same as that of the Euler method. Midpoint initially requires to compute the Euler step. Additionally, the derivates are calculated again at the steps midpoint. This helps to estimate more accurate value at the next time step. It also handles the circular motion of the particle in a better manner.

### Benchmarks
By carefully examining the insights of both the solvers, the computation time taken by Midpoint method was more as compared to the Euler method justifying the fact that the derivates are being calculated twice. Below Figures show how the cloth being simulated with spring forces holding the particles together.

### Conclusion
Cloth was simulated with the numerous small particles. To attach the particles with the forces, 4 springs are used to the join every adjacent particles. (2 in X and Y directions and the other 2 in diagonals). Although much difference was not seen while examining the cloth by different solvers, Midpoint Method animated the cloth in a better manner due to much accurate approximations and also became stable at a faster rate than the Euler method


## 3) Steering Behaviors for Autonomous characters

### Introduction
In this Project, steering behaviors for autonomous characters are implemented. Different combinations of steering behaviors are used to achieve higher level goals such as avoiding obstacles while characters are in motion and making the characters follow the leader. We implemented various steering behaviors described below:
i. Seek: steers towards a static target
ii. Flee: steers away from a static target
iii. Pursuit: Pursuit is similar to seek except that the target is in motion.
iv. Evasion: In Evasion, the target moves away from a moving pursuer.
v. Collision detection and avoidance: to avoid collision between characters and other.

### Design and Methodology:
Based on above-mentioned steering behaviors, we used 3 different scenarios for simulation:
i. Scenario-1:
The intended goal is to implement basic seek, flee, pursuit and evade for one character and single target. Two algorithms for pursuit are implements.
ii. Scenario-2:
In the second scenario, a scene to simulate an army following a leader to attack a kingdom is implemented using the steering behaviors. They assemble at a point and attack. When the kingdom is attacked the king evades and the army’s top five agents pursue to capture.
iii. Scenario-3:
In the third scenario, troops assemble at a point from random positions with random velocities. They have
to form a circle at the assembly point. Collision detection and avoidance enabled a circle to be formed. The troops attack the kingdom, forming a line to attack. Figure shows this scene.

### Implementation challenges:
The challenges that we faced were mostly collision detection and avoidance between characters. The algorithm used was effective in detecting obstacles/ characters towards the character’s velocity.

### Performance Evaluation:
Scenario 1:
i. Two pursuit algorithms were evaluated; it was found that the algorithm that approaches the evader from its predicted future position caught the evader in an earlier time.
Scenario 2:
i. Different velocities were used to pursue the king. As expected the higher the velocity of the pursuer the king is captured. However, when the king’s velocity is greater than agent’s velocity, the king is not captured.
Scenario 3:
i. Adjusting the number of character: As the number of characters is increased, it becomes difficult to handle collision detection and form a perfect circle at the center. Some characters remain behind other particles as shown in . As the number of character go above 30.
ii. With a higher velocity the line formed to attack the kingdom is also not perfect. Collision detection is not perfect..
iii. When the agents are moving with different velocities, it is difficult to detect collision between them as some of them will come closer and some will go far apart (Unlike in Scenario-2).

### Conclusion: 
In this project, various new topics were studied and evaluated. Different functions used by autonomous characters have been implemented such as seek, flee, pursue, evade, collision detection and avoidance. The algorithm used for collision avoidance can be improved so pursuing and attacking can be effectively done, especially when velocities are random or high.
