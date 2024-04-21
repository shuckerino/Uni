from Classes import PerceptronBase
from typing import List, Any

class PerceptronWithBias(PerceptronBase.PerceptronBase):
    
    def __init__(self, dimensions : int, alpha: float = 1.0, bias : float = 0):
        super().__init__(alpha=alpha, weights=[dimensions + 1])
        self.bias = bias
        
    def classify(self, data_point : List[float]) -> int:
        pass
    
    def train(self, dataset : List[float], classes : List[int]):
        pass
    
    