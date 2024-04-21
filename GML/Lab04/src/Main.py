from Classes import PerceptronBase, Perceptron, PerceptronWithBias
from Classes.Instance import Instance
from IO.CsvHelper import split_dataset, get_objects_from_csv
import numpy as np

if __name__ == "__main__":

    # load dataset from csv
    csv_data = get_objects_from_csv("../resources/uebung03.csv")
    
    # convert csv rows to Instances
    instances = [Instance(i, [0, 1], 6, "ja") for i in csv_data]
    
    # split into training and validation set
    training_set, validation_set = split_dataset(instances, 0.5)
    
    print("Total size of data set is {0}".format(len(csv_data)))
    print("Total size of training set is {0}".format(len(training_set)))
    print("Total size of validation set is {0}".format(len(validation_set)))
    
    # assign weights
    weights = np.array([0.1, 0.1])
    normal_perceptron = Perceptron.Perceptron(weights, 0.1)
    
    # classify and print
    for instance in validation_set:
        res = normal_perceptron.classify(instance.values)
        print("Classification result is {0}".format(res))
    
    
    