#!/bin/python3

import numpy as np
import matplotlib.pyplot as plt
import math
import matplotlib.patches as patches

p1 = np.array([1, 1, 1, 1])
p2 = np.array([3, 1, 1, 1])
p3 = np.array([3, 3, 1, 1])
p4 = np.array([1, 3, 1, 1])

rotation_angle = 45.0
transformation_matrix = np.array([[math.cos(rotation_angle), -math.sin(rotation_angle), 0, 2],
                                 [math.sin(rotation_angle), math.cos(rotation_angle), 0, 1],
                                 [0, 0, 1, 0],
                                 [0, 0, 0, 1]])

print(transformation_matrix)

p1_transformed = transformation_matrix @ p1
p2_transformed = transformation_matrix @ p2
p3_transformed = transformation_matrix @ p3
p4_transformed = transformation_matrix @ p4

print(20 * "#")
print(p1_transformed)
print(p2_transformed)
print(p3_transformed)
print(p4_transformed)

fig, ax = plt.subplots(figsize= (5, 5))
ax.set_xlim(-2, 10)
ax.set_ylim(-2, 10)

# Plotting old rectangle
old_rect_corners = np.vstack([p1, p2, p3, p4, p1])
x, y = old_rect_corners[:, 0], old_rect_corners[:, 1]
ax.plot(x, y, 'b-', linewidth=2)

# Plotting new rectangle
new_rect_corners = np.vstack([p1_transformed, p2_transformed, p3_transformed, p4_transformed, p1_transformed])
x, y = new_rect_corners[:, 0], new_rect_corners[:, 1]
ax.plot(x, y, 'r-', linewidth=2)

plt.show()