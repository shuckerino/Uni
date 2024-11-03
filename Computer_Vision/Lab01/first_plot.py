import matplotlib.pyplot as plt
import numpy as np

# Create the two vectors which should be plotted
data = np.array([[1,6],
                  [9,22]])
# Get data points for time and velocity
time = data[:, 0]
speed = data[:, 1]

fig = plt.figure(figsize = (5,5))
plt.plot(time,speed, "r-", label="Function of car velocity over time")

# Label the plot
plt.xlabel("Time in sec")
plt.ylabel("Velocity in km/h")
plt.title("Data points of car velocity")
plt.grid(True)
plt.legend()

# Show the plot
plt.show()
