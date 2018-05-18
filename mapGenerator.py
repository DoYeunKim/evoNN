import argparse, copy, csv
from random import randrange
import random
parser = argparse.ArgumentParser()

# Terrain class
# Each terrain has type, coordinate, nourishment score range, and danger score range
class Terrain:
	t_type = -1
	t_x = t_y = 0
	n_min = n_max = d_min = d_max = 0.0

class frontInfo:
	f_type = f_x = f_y = 0

def parseArg():
	# We want to read in x dimension, y dimension, and the maximum nourishment level of the terrain
	# This list will get bigger as more attributes are added to the map
	parser.add_argument("x_dim", help="The x-dimension of the map being created. x must be an int of at least 1")
	parser.add_argument("y_dim", help="The y-dimension of the map being created. y must be an int of at least 1")
	parser.add_argument("min_nour", help="The minimum level of tile nourishment in this world. [0.0, 1.0)")
	parser.add_argument("max_nour", help="The maximum level of tile nourishment in this world (0.0, 1.0]")

	args = parser.parse_args()
	x = int(args.x_dim)
	y = int(args.y_dim)
	minN = float(args.min_nour)
	maxN = float(args.max_nour)
	

	if (x < 1 or y < 1):
		print("Illegal map dimensions.")
		exit(1)
	
	if (minN > maxN):
		print("Minimum level of tile nourishment cannot be greater than maximum level of tile nourishment.")
		exit(1)
	
	if (minN >= 1.0 or minN < 0.0):
		print("Minimum level of tile nourishment must fall in the range of: [0.0, 1.0)")
		exit(1)
	
	if (maxN > 1.0 or maxN <= 0.0):
		print("Maximum level of tile nourishment must fall in the range of: (0.0, 1.0]")
		exit(1)

	mapGenerator(x, y, minN, maxN)

def mapGenerator(x, y, minN, maxN):

	# Define Barren terrain	
	# Barren terrain is the most barren of the three terrains, with relatively high danger score
	# While nourishment score is based on user input, danger score is currently arbitrary numbers
	b_factor = 0.3
	Barren = Terrain()
	Barren.t_type = 0
	Barren.n_min = minN
	if (minN < maxN):
		Barren.n_max = Barren.n_min + (maxN - minN) * b_factor
	else:
		Barren.n_max = Barren.n_min
	Barren.d_min = 0.02
	Barren.d_max = 0.05

	# Define Medium terrain
	# Medium terrain is in the middle of the three terrains in terms of food and danger scores
	# While nourishment score is based on user input, danger score is currently arbitrary numbers
	m_factor = 0.5
	Medium = Terrain()
	Medium.t_type = 1
	Medium.n_min = Barren.n_max
	if (minN < maxN):
		Medium.n_max = Medium.n_min + (maxN - minN) * m_factor
	else:
		Medium.n_max = Medium.n_min
	Medium.d_min = 0.01
	Medium.d_max = 0.04

	# Define Fertile terrain
	# Fertile terrain is the most fertile of the three terrains, with a wide range of danger score
	# While nourishment score is based on user input, danger score is currently arbitrary numbers
	f_factor = 1
	Fertile = Terrain()
	Fertile.t_type = 2
	Fertile.n_min = Medium.n_max
	if (minN < maxN):
		posMax = Fertile.n_min + (maxN - minN) * f_factor
		if posMax > maxN:
			Fertile.n_max = maxN
		else:
			Fertile.n_max = posMax
	else:
		Fertile.n_max = Fertile.n_min
	Fertile.d_min = 0.02
	Fertile.d_max = 0.06
	
	# List of each terrains, used to seed the map with terrain seeds
	# terrainDiversity is used to determine the number of iteration the seeds are placed in the world
	terrains = [Barren, Medium, Fertile]

	nourishment_map = [([0.0] * x) for row in range(y)]
	danger_map = [([0.0] * x) for row in range(y)]
	terrain_map = [([-1] * x) for row in range(y)]
	fronts = []
	populated = []

	# Plant seeds for terrains
	for t in terrains:
		seed = False		
		while (seed == False):
			xRand = randrange(x)
			yRand = randrange(y)
			if terrain_map[xRand][yRand] == -1:
				t.t_x = xRand
				t.t_y = yRand
				
				terrain_map[xRand][yRand] = t.t_type
				nourishment_map[xRand][yRand] = random.uniform(t.n_min, t.n_max)
				danger_map[xRand][yRand] = random.uniform(t.d_min, t.d_max)

				front = frontInfo()
				front.f_x = t.t_x
				front.f_y = t.t_y
				front.f_type = t.t_type
				fronts.append(front)
				seed = True

	populateTerrains(nourishment_map, danger_map, terrain_map, fronts, Barren, Medium, Fertile, x, y, populated)
	bTot = mTot = fTot = 0
	for i in terrain_map:
		print(i)
	print("\n")
	for j in nourishment_map:
		print(j)
	print("\n")
	for k in danger_map:
		print(k)
	
	ter_csv = str(x) + "x" + str(y) + "_" + str(minN) + "x" + str(maxN) + "_terrain.csv"
	with open(ter_csv, "w+") as my_csv:
		csvWriter = csv.writer(my_csv, delimiter = ",")
		csvWriter.writerows(terrain_map)

	nour_csv = str(x) + "x" + str(y) + "_" + str(minN) + "x" + str(maxN) + "_nourishment.csv"
	with open(nour_csv, "w+") as my_csv:
		csvWriter = csv.writer(my_csv, delimiter = ",")
		csvWriter.writerows(nourishment_map)

	dan_csv = str(x) + "x" + str(y) + "_" + str(minN) + "x" + str(maxN) + "_danger.csv"
	with open(dan_csv, "w+") as my_csv:
		csvWriter = csv.writer(my_csv, delimiter = ",")
		csvWriter.writerows(danger_map)

def populateTerrains(nourishment_map, danger_map, terrain_map, fronts, Barren, Medium, Fertile, x, y, populated):
	bTot = mTot = fTot = 0	
	# Want to populate the world with terrain until the entire map is filled
	maxSize = sum(len(x) for x in terrain_map)

	while len(populated) < maxSize:
		# Queue of some sort
		front = fronts.pop(0)
		tType = terrain_map[front.f_x][front.f_y]
		populated.append(front)

		#print(len(populated), "tiles populated so far")
		#print(tType)
		
		# I am pushing in pre-defined terrain type, so check that whatever has been input is a defined terrain
		if tType > -1:
			# Load appropriate terrain type
			t = Terrain()
			if tType == 0:
				t = copy.deepcopy(Barren)
				bTot += 1
			elif tType == 1:
				t = copy.deepcopy(Medium)
				mTot += 1
			elif tType == 2:
				t = copy.deepcopy(Fertile)
				fTot += 1		

			# Check that the neighbors are within the bounds of the map and that the neighbor is not yet defined
			for fx in range(front.f_x-1, front.f_x+2):
				if fx < 0 or fx >= x:
					#print("out of bounds")
					continue
				for fy in range(front.f_y-1, front.f_y+2):
					if fy < 0 or fy >= y:
						#print("out of bounds")
						continue
					if terrain_map[fx][fy] != -1:
						#print("already populated")
						continue
					
					# Assign terrain type to the neighbor
					#print("Populating (" + str(fx) + "," + str(fy) + ")")
					terrain_map[fx][fy] = t.t_type
					nourishment_map[fx][fy] = random.uniform(t.n_min, t.n_max)
					danger_map[fx][fy] = random.uniform(t.d_min, t.d_max)

					# Push the neighbor into the queue
					neighbor = frontInfo()
					neighbor.f_x = fx
					neighbor.f_y = fy
					neighbor.f_type = tType	
					fronts.append(neighbor)

	print("There are: " + str(bTot) + " barren tiles, " + str(mTot) + " medium tiles, and " + str(fTot) + " fertile tiles on this " + str(x) + "x" + str(y) + " world")	

parseArg()

