import csv
import sys
import os
import random

def get_objects_from_csv(filename:str) -> list:

    if os.path.exists(filename):
        with open(filename, 'r', encoding='ISO-8859-1') as file:
            reader = csv.reader(file, delimiter=";")
            
            # skip header row
            next(reader)
            
            return list(reader)
    else:
        print("Could not find passed filename. Please try again!")
        return None
    
    
def split_dataset(data, ratio):
    random.shuffle(data)
    split_number = int(ratio * len(data))
    #print("split number is {0}".format(split_number))
    training_set = data[:split_number]
    validation_set = data[split_number:]
    #print("Training set length: {0}".format(len(training_set)))
    #print("Validation set length: {0}".format(len(validation_set)))
    return training_set, validation_set
