#!/bin/python3

import numpy as np

# Given points
p = np.array([
    [-1, -1],
    [1, -1],
    [1, 1],
    [-1, 1]
])

p_prime = np.array([
    [3, 3],
    [3, 5],
    [5, 5],
    [5, 3]
])

# Constructing matrix A
A = []

for i in range(4):
    x, y = p[i][0], p[i][1]
    x_prime, y_prime = p_prime[i][0], p_prime[i][1]
    
    A.append([x, y, 1, 0, 0, 0, -x*x_prime, -y*x_prime, -x_prime])
    A.append([0, 0, 0, x, y, 1, -x*y_prime, -y*y_prime, -y_prime])

A = np.array(A)

print(f"Matrix A is: \n{A}")

# Performing SVD
U, S, Vt = np.linalg.svd(A)

# The homography matrix is the last row of V (or Vt.T) reshaped to 3x3
H = Vt[-1].reshape(3, 3)

print("Homography matrix H:")
print(H)
