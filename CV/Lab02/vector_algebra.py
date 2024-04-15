#!/bin/python3

import numpy as np

# define vectors
p1 = np.array([2, 4, 1])
p2 = np.array([5, 3, 1])
p3 = np.array([7, 12, 1])
p4 = np.array([3, 8, 1])
p5 = np.array([10, 6, 2])

l1 = np.array([-2, 1, 1])
l2 = np.array([2, 3, 1])



# a - Addition of p1 and p2
res = np.add(p1, p2)
print("Solution for a) is {}".format(res))

# b - Subtraction of p3 and p2
res = np.subtract(p3, p2)
print("Solution for b) is {}".format(res))

# c - Multiplication of 5 and p4
res = np.dot(5, p4)
print("Solution for c) is {}".format(res))

# d - Dot product of p2 and p4
res = np.dot(p2, p4)
print("Solution for d) is {}".format(res))

# e - Cross product of p2 and p4
res = np.cross(p2, p4)
print("Solution for e) is {}".format(res))

res = np.cross(l1,l2)
print("Solution for g) is {}".format(res))

print("Last result is {}".format(np.dot(np.array([-400, 1200, -880000]), np.array([1046, 1282, 1]))))
