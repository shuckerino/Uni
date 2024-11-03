#!/usr/bin/env python3

TRAINING_DATA = {"Hund1": (100, 200, 110, 120), "Katze": (210, 220, 100, 250), "Hund2": (200, 210, 120, 110), "Vogel": (20, 100, 90, 200)}

TEST_DATA = {1: (200, 100, 220, 200), 2: (30, 110, 120, 100), 3: (220, 120, 100, 120)}

def euclidean_distance(data_point1, data_point2):
    distance = 0
    for i in range(len(data_point1)):
        distance += (data_point1[i] - data_point2[i])**2
    return distance**0.5

def manhattan_distance(data_point1, data_point2):
    distance = 0
    for i in range(len(data_point1)):
        distance += abs(data_point1[i] - data_point2[i])
    return distance

if __name__ == "__main__":
    print("KNN.py is running...")
    for image in TEST_DATA:
        l1_distances = dict()
        l2_distances = dict()
        for key in TRAINING_DATA:
            l1_distances[key] = manhattan_distance(TRAINING_DATA[key], TEST_DATA[image])
            l2_distances[key] = euclidean_distance(TRAINING_DATA[key], TEST_DATA[image])
        # print(f"All distances for image {image}: {l2_distances}")
        l1_key = min(l1_distances, key=l1_distances.get)
        l2_key = min(l2_distances, key=l2_distances.get)
        print(f"Image {image} is most similar to {l1_key} ({l1_distances[l1_key]}) using L1 metric")
        print(f"Image {image} is most similar to {l2_key} ({l2_distances[l2_key]}) using L2 metric")


    