import numpy as np

def calculate_hamming_distance(pattern : str, neighbour : str) -> int:
    '''Compare two patterns of same length and return their hamming distance'''
    if len(pattern) != len(neighbour):
        return -1
    hamming_distance = 0
    for i in range(0, len(pattern)):
        if pattern[i] != neighbour[i]:
            hamming_distance += 1
            
    return hamming_distance

def cost(a, b):
    if a == b:
        return 0  # Match
    return 1  # Mismatch

def read_sequences(file_path):
    #return "TTGTTATA", "ATCGTCC"
    """Reads sequences from a file."""
    with open(file_path, 'r') as file:
        sequences = file.readlines()
    return sequences[1].strip(), sequences[2].strip()

def global_alignment_bb(seq1, seq2):
    num_bb = 0
    n = len(seq1)
    m = len(seq2)
    gap_costs = 1
    hamming_distance = calculate_hamming_distance(seq1, seq2)
    
    # 
    expected_costs = hamming_distance + abs(len(seq1) - len(seq2))

    # Initialize the cost and traceback matrix
    cost_matrix = np.zeros((n + 1, m + 1), dtype=float)
    traceback_matrix = np.zeros((n + 1, m + 1), dtype=str)

    # Initialize the first column
    for i in range(1, n + 1):
        cost_matrix[i][0] = i * gap_costs
        traceback_matrix[i][0] = 'U'  # Up

    # Initialize the first row
    for j in range(1, m + 1):
        cost_matrix[0][j] = j * gap_costs
        traceback_matrix[0][j] = 'L'  # Left

    # Fill in the scoring matrix and traceback matrix
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            match_cost = cost(seq1[i - 1], seq2[j - 1])
            match = cost_matrix[i - 1][j - 1] + match_cost
            delete = cost_matrix[i - 1][j] + gap_costs
            insert = cost_matrix[i][j - 1] + gap_costs
            print(f"Match cost: {match}, Delete cost: {delete}, Insert cost: {insert}")
            current_costs = min(match, delete, insert)
            
            # If the total costs until now are already higher than our expected cost, branch
            if current_costs > expected_costs:
                num_bb += 1
                cost_matrix[i][j] = np.inf
                traceback_matrix[i][j] = 'B'
            else:
                cost_matrix[i][j] = current_costs
                # Mark cell for backtracking
                if cost_matrix[i][j] == match:
                    traceback_matrix[i][j] = 'D'  # Diagonal
                elif cost_matrix[i][j] == delete:
                    traceback_matrix[i][j] = 'U'  # Up
                else:
                    traceback_matrix[i][j] = 'L'  # Left
                    
            #threshold = min(threshold, min_costs)
    with open("log.txt", "w") as logfile:
        logfile.write("###################Cost matrix################\n")
        logfile.write(np.array2string(cost_matrix, threshold=np.inf, max_line_width=np.inf))
        logfile.write("\n###################Cost matrix################\n")
        logfile.write("\n")
        logfile.write("\n###################Traceback matrix################\n")
        logfile.write(np.array2string(traceback_matrix, threshold=np.inf, max_line_width=np.inf))
        logfile.write("\n###################Traceback matrix################\n")
    
    # If the best found cost is still larger than our threshold, then there is no solution
    if cost_matrix[n][m] == np.inf:
        return np.inf, None, None
    
    # Traceback to find the alignment
    align1, align2 = '', ''
    i, j = n, m

    while i > 0 or j > 0:
        if traceback_matrix[i][j] == 'D':
            align1 = seq1[i - 1] + align1
            align2 = seq2[j - 1] + align2
            i -= 1
            j -= 1
        elif traceback_matrix[i][j] == 'U':
            align1 = seq1[i - 1] + align1
            align2 = '-' + align2
            i -= 1
        elif traceback_matrix[i][j] == 'L':
            align1 = '-' + align1
            align2 = seq2[j - 1] + align2
            j -= 1

    print(f"Number of branch&bounds: {num_bb}")
    return cost_matrix[n][m], align1, align2

def main():
    #s = "ATGTTATA"
    #t = "ATCGTCC"
    sequences_file = "./input.txt"
    s, t = read_sequences(sequences_file)
    print(f"s is {s}")
    print(f"t is {t}")
    
    result_costs, alignment1, alignment2 = global_alignment_bb(s, t)
    print(f"Alignment costs: {result_costs}")
    print(f"Best found alignments:\n")
    print(alignment1)
    print(alignment2)

if __name__ == "__main__":
    main()
