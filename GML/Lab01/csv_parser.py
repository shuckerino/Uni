import csv
import sys
import os

if len(sys.argv) > 1:
    filename = sys.argv[1]

    if os.path.exists(filename):
        with open(filename, 'r', encoding='ISO-8859-1') as file:
            reader = csv.reader(file, delimiter=";")

            for row in reader:
                    print(row)
    else:
        print("Could not find passed filename. Please try again!")
else:
    print("You need to pass in a filename of the csv that should be read!")
