import csv
import random
import sys
import os

def split_dataset(data, ratio):
    random.shuffle(data)
    split_number = int(ratio * 100)
    training_set = data[:split_number]
    validation_set = data[split_number:]
    return training_set, validation_set


if len(sys.argv) > 2:
    filename = sys.argv[1]
    training_set_ratio = float(sys.argv[2])

    if os.path.exists(filename):
        with open('uebung01.csv', 'r', encoding='ISO-8859-1') as file:
            reader = csv.reader(file)
            
            data = []
            for row in reader:
                data.append(row)
                # print(row)


            training_set, validation_set = split_dataset(data, training_set_ratio)
            
            print(20 * "#")
            print("Length of training set: {0}".format(len(training_set)))

            # for l in training_set:
            #     print(l)

            print(20 * "#")
            print("Length of validation set: {0}".format(len(validation_set)))

            # for l in validation_set:
            #     print(l)
    else:
        print("Could not find passed filename. Please try again!")
else:
    print("You need to pass in a filename of the csv that should be read and the ratio that should be the training set!")
