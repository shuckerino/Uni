#!/bin/python3

import numpy as np

P = np.array([[240, 0, 200], [0, 240, 150], [0, 0, 0]])
vec = np.array([50, 200, 150])

# q = np.array([[-0.4, -2, -1.8], [-1.4, -1, 1.2], [0.6, 0, 0.2], [1.6, 1, -0.8], [-0.4, 2, 1.2]])
# q_transformed = np.array([[-1.8, -2, 0.4], [1.2 -1, 1.4], [0.2, 0, 0.6], [-0.8, 1, -1.6], [1.2, 2, 0.4]])

# print(np.linalg.solve(P, vec))
# print(np.transpose(q) @q_transformed)

H = np.array([[-2.6, 3, -5.2], [4, 10, -3], [6.8, 4, 2.6]])

svd = np.linalg.svd(H)
print(f"S is {svd.S}")
print(f"U is {svd.U}")
print(f"V is {svd.Vh}")

# Calculate X
X = svd.Vh.transpose() @ svd.U.transpose()

print(f"X is {X}")

# Check if determinant is 1
print(f"Det is {np.linalg.det(X)}")

