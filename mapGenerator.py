import argparse
import csv
import random
parser = argparse.ArgumentParser()

def parseArg():
	# We want to read in x dimension, y dimension, and the maximum nourishment level of the terrain
	# This list will get bigger as more attributes are added to the map
	parser.add_argument("x_dim", help="The x-dimension of the map being created")
	parser.add_argument("y_dim", help="The y-dimension of the map being created")
	parser.add_argument("min_nour", help="The minimum level of title nourishment in this world")
	parser.add_argument("max_nour", help="The maximum level of tile nourishment in this world")

	args = parser.parse_args()
	mapGenerator(args)

def mapGenerator(args):
	x = int(args.x_dim)
	y = int(args.y_dim)
	minN = int(args.min_nour)
	maxN = int(args.max_nour)
	
	mapGen = [[random.uniform(minN, maxN) for i in range(y)] for j in range(x)]	

	csv_name = str(x) + "x" + str(y) + "_" + str(minN) + "x" + str(maxN) + ".csv"
	with open(csv_name, "w+") as my_csv:
		csvWriter = csv.writer(my_csv, delimiter = ",")
		csvWriter.writerows(mapGen)

parseArg()

