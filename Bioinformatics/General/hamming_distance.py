def calculate_hamming_distance(pattern : str, neighbour : str) -> int:
    '''Compare two patterns of same length and return their hamming distance'''
    if len(pattern) != len(neighbour):
        return -1
    hamming_distance = 0
    for i in range(0, len(pattern)):
        if pattern[i] != neighbour[i]:
            hamming_distance += 1
            
    return hamming_distance