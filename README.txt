************************************************************************************************************************************************************************************************************
Evolutionary Neural Network: an experiment to create intelligent evolving creatures
by Do Yeun Kim
for Cognitive Architecture course at Bowdoin, Brunswick ME (Spring 2018)
************************************************************************************************************************************************************************************************************

This is my attempt to create a small world in which creatures with simple Neural Nets (NN) roam around, learning its environment. 
This project was inspired by Braitenberg's Vehicles and Guppies video by Aritifical Life Experiments on youtube (https://www.youtube.com/watch?v=tCPzYM7B338).

The project currently consists of two major steps - map generation and running the world.
Each step is written in Python and c++, respectively.


The Python script, mapGenerator.py, generates a world of user input dimensions and the minimal and maximal levels of nourishment, then creates a world. 
It currently can produce a world of three terrains: barren, medium, and fertile.
These terrains are first seeded then propagated through BFS.
Each terrain as a range of nourishment and a range of danger level.
While nourishment score feeds the creatures (increasing their energy level needed to keep them alive) and increases their fitness, danger score harms the creatures (reducing their health) and reduces their fitness. 
Currently danger level is manually set in the script.
The script should be outputting the resulting map and the number of tiles per each terrain, so do check that the map is what you would like to run the experiments on.
Also note that the script outputs a .csv file for three different factors - nourishment, danger, and terrain.
All of these are to be read in by the C++ program, the method of which is explained below.

As for the C++ part, note that THEY ARE WRITTEN TO SUPPORT C++11.
The program consists of the main class, World, which contains the map and the creatures.
The map consists of read in information and the number of creatures present.
The creatures are members of class Creature, and each have simple perceptron feed-forward networks, borrowed from my Neural Net project with David Reichert and Osborn Yator in Nature-Inspired Computations.
Input layer consists of the creature's visual field, set as a square area with the radius of variable vision, set in Creature.hpp.
Output layer consists of 8 cardinal directions and the current position in the case the animal were to decide to not move.
In this project, the creatures need to explore the World while sustaining themselves by getting to locations with nourishment score but also avoiding locations with high danger score.
As noted above, being exposed to high danger score can physically damage the creatures.
At the end of each generation, the number of epochs for which is set in main.cpp as of now, the weights of edges (or the "brain") of the most fit creature is copied and transplanted to the new generation.

************************************************************************************************************************************************************************************************************
As of now, I am suffering from two major problems with brain transplant.
1. While the brain is correctly inherited through the layers of classes, it seems that once the brain of the parent is copied, it is somehow immediately modified. 
	As I do not call a function that does this immediately following inheritance, I am unsure as to what can be causing the problem. 
	The next step to solving this would be using valgrind.
2. Even though the brain is not being properly transplanted, there is also a problem where when the world terminates prematurely due to all individuals dying out, the next generation defaults to fitness = 0.
	I have observed some cases in which the animals were able to "do better" than all 0's, they are infrequent and short-lived.

Also, there is a great number of variables that can be and should be tweaked for both Python script and C++ program. 
However as I have been focusing on putting the World together, I am yet to allow the program to actually get modified by the input parameters.
For the time being, please use the default parameters.
************************************************************************************************************************************************************************************************************


************************************************************************************************************************************************************************************************************
To use this program, do the following:

1. Run the Python script named mapGenerator.py with appropriate parameters (x-dimension, y-dimension, minimum-nourishment [0.0,1.0), maximum-nourishment (0.0,1.0])
	It should produce three .csv files named [x-dim]x[y-dim]_[min-nourishment]x[max-nourishment]_[danger, nourishment, or terrain].csv
	I am going to call the part leading up to the last field (dimension_nourishment_) the "common part."
2. Compile with -std=c++11
3. Run the C++ program with the "common part" as the input (You can provide others shown with usage function, but they are not going to be reflected for now)
4. You will be able to see some stats on generation fitness and the world upon termination.


************************************************************************************************************************************************************************************************************

This project turned out to have three phases.

<PHASE 1>
Creating a world with creatures with NN, where the world looks like this:
	
	0 0 0 0 1 1 2 1 
	1 0 0 1 1 0 0 0 
	0 2 0 1 0 0 1 1  
	1 0 0 0 0 1 0 0 
	0 0 0 1 1 0 0 0  
	2 1 0 1 1 0 0 0 
	0 0 0 0 1 0 1 0
	1 1 0 0 1 0 0 0
	
	Here, each grid consisted of whether there is nothing, food, or a creature.
	In this system, the creatures would roam around and upon encountering a tile with food, would gain energy and fitness score.
	They were given information to the restricted visual field starting at this phase.
	The creatures were penalized heavily when not eating, by the means of reduction in energy level after going through some starvation period.
	I did not have the python script at this point and was randomly generating the world for each run.
	At this point I had not implemented generations.

	Phase 1 took me just over a week to "finish."


<PHASE 2>
Transitioning the world to use "sustainability score" per suggestion by Professor Nascimento:
	
	At this point, the grid looked pretty much like it does now, except that the world only contained what I now call "nourishment score."
	Since I realized that randomly generating the world per run would prevent the creatures from truly learning the world between generations, I decided to make persistent maps.
	I thus wrote mapGenerator.py to generate the world and feed it to the C++ program. 
	As I wanted nourishment score to be doubles of range [0.0,1.0], I had to change the types around for the map and NN, and change how the creatures perceive the world.
	Also, the tiles do not just indicate whether there is a creature there, but the number of the creatures at the location.
	After I had transitioned to "nourishment score" system, I was able to really get started with experimenting with the NN's as the randomness of the world was removed.

	Phase 2 took me about half a week.


<PHASE 3>
Adding "danger score" and balancing the world per suggesting by Professor Chown:

	In PHASE 2, the Malthusian trap was in full effect.
	The animals were dying out for the following reasons:
		1. Food was getting exhausted extremely quickly because I was not balancing consumption rate and food regrowth
		2. Apart from starvation, the creatures were devoid of threats.
		3. Something was wrong with brain transplant, especially in the case of premature termination of the World.

	I was able to address the first two problems.
	1. Addressing the first issue, I realized that the regrowth function was not directly tweaking the map, but just a copy of it.
		Also I had to (and am still trying to ) better balance consumption rate and regrowth rate.
	2. I introduced "danger score," as mentioned above.
		Now mapGenerator.py outputs terrain type, nourishment score, and danger score, all of which are incorporated into the World.
		Danger score and nourishment score are both scaled and limited by terrain type.
		The creatures in the given tile share the burden of danger, so danger score scales inversely to the number of creatures.
		With the probability of the divided danger score, a creature gets hurt (decrease in health).
		Thus now the creatures can get killed not just from starving but from venturing into dangerous areas.
		
	Again, issue 3 is yet to be addressed.
	
	Phase 3 took about a week to work on, and as I am out of time, it is "finished" as of now.


************************************************************************************************************************************************************************************************************

Observations

I used most of my time building and rebuilding the world, and have not had time to run enough experiments to provide conclusive remarks.
However I list some findings here:

1. The single layer perceptron system I have is most likely inadequate to show complex behaviors.
	The Guppies experiment, one of the inspirations for this project, uses 80+ nodes for hidden layers and employ Recurring Network and Long Short-Term Memory Network.
	This project is far from getting to such level of complexity and thus is not expected to produce "complex" behaviors.
2. Balancing and maintaining a World is quite difficult.
	When I started adding attributes such as starvation and energy, the World became drastically more complex. 
	As we talked about in Cog Arch, there is just too much information in this large World, and it is definitely challenging to weave all of them when building a world.
	There is much of fine tuning that needs to be performed especially if I want the World to be dynamic.
3. Penalizing and rewarding is difficult.
	I may be penalizing the creatures too much upon starvation while penalizing them equally for moving.
	While I am penalizing their movement as that is what happens in the real world, I am wondering if I should rethink on how starvation and movement work.
	At a point I thought of restricting the creatures' activity level upon starvation, but it got too complicated.


************************************************************************************************************************************************************************************************************

Future Direction

There is a lot that can be done to improve on this project.
However, here is a short priority list:

1. Fix all the problems listed above. I cannot quite move forward without solving them (brain transplant and user input)
2. To improve brain transplant idea, incorporate Genetic Algorithms
3. Implement hidden layers and back propagation
4. Diversify the ecosystem by adding subclasses of creatures or by allowing the creatures to gain energy by attacking others
5. Diversify the terrains
6. Visualization

************************************************************************************************************************************************************************************************************
