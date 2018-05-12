import argparse
import csv
import random
parser = argparse.ArgumentParser()

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
	
	mapGen = [[random.uniform(minN, maxN) for i in range(y)] for j in range(x)]	

	csv_name = str(x) + "x" + str(y) + "_" + str(minN) + "x" + str(maxN) + ".csv"
	with open(csv_name, "w+") as my_csv:
		csvWriter = csv.writer(my_csv, delimiter = ",")
		csvWriter.writerows(mapGen)

parseArg()

