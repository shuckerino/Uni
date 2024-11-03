from Classes.PerceptronBase import PerceptronBase
import numpy as np
from typing import List

class Perceptron(PerceptronBase):

    #region Ctor

    def __init__(self, weights, alpha=0.01):
        super().__init__(alpha=alpha, weights=weights)

    #endregion

    #region Methods

    def augment(self, data_point) -> np.array:
        ''' Augments a vector by one dimension, example: [4.0, 1.2] -> [1.0, 4.0, 1.2]'''
        return np.concatenate(([1.0], data_point))
        
    def classify_augmented(self, augmented_data_point) -> int:
        print("Weights are {0}".format(self.weights))
        print("augmented data point is are {0}".format(augmented_data_point))
        res = np.dot(self.augment(self.weights), augmented_data_point)
        print("Result of classification is {0}".format(res))
        if res >= 0:
            return 1
        else:
            return 0

    def classify(self, data_point: List[float]) -> int:
        augmented_data_point = self.augment(data_point)
        return self.classify_augmented(augmented_data_point)

    def train(self, dataset, classes) -> bool:
        pass

    #endregion