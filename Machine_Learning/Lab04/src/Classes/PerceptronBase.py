from abc import ABC, abstractmethod

class PerceptronBase(ABC):

    # Constructor
    @abstractmethod
    def __init__(self, alpha, weights):
        self.alpha = alpha
        self.weights = weights

    # Classify given data point in class 0 or 1
    @abstractmethod
    def classify(self, data_point) -> int:
        pass

    # Train the perceptron with the given dataset and classes
    @abstractmethod
    def train(self, dataset, classes) -> bool:
        pass