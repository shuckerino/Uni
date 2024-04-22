#!/bin/python3

import numpy as np

p1 = np.array([500, 250, 1])
p2 = np.array([870, 1260, 1])
l2 = np.array([-770, -370, 866000])
l3 = np.array([-40, -370, 501000])

# a
l1 = np.cross(p1, p2) 
print(l1)
l1_normalized = l1 * (1/412500)
print(l1)

#b
intersect_l1_l2 = np.cross(l1, l2)
#intersect_l1_l2_v2 = np.cross(l1_normalized, l2)
print("Normal: {0}".format(intersect_l1_l2))
#print("Normalized: {0}".format(intersect_l1_l2_v2))

intersect_1_normalized = intersect_l1_l2 * (1/658600)
print("Normalized: {0}".format(intersect_1_normalized))
#print("V1 Normalized: {0}".format(intersect_1_normalized))
#intersect_2_normalized = intersect_l1_l2_v2 * (1/1.59660606)
#print("V2 Normalized: {0}".format(intersect_1_normalized))