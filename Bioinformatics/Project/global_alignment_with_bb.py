import numpy as np
from General.hamming_distance import calculate_hamming_distance

def read_blosum62(file_path):
    """Reads the BLOSUM62 matrix from a file and returns it as a dictionary."""
    with open(file_path, 'r') as file:
        lines = file.readlines()

    headers = lines[0].strip().split()
    blosum62 = {}

    for line in lines[1:]:
        parts = line.strip().split()
        row_char = parts[0]
        scores = list(map(int, parts[1:]))
        blosum62[row_char] = {headers[i]: scores[i] for i in range(len(headers))}

    return blosum62

def cost(a, b):
    if a == b:
        return 0  # Match
    return 2  # Mismatch

def read_sequences(file_path):
    #return "TTGTTATA", "ATCGTCC"
    """Reads sequences from a file."""
    with open(file_path, 'r') as file:
        sequences = file.readlines()
    return sequences[1].strip(), sequences[2].strip()

def global_alignment_bb(seq1, seq2):
    n = len(seq1)
    m = len(seq2)
    gap_costs = 1
    hamming_distance = calculate_hamming_distance(seq1, seq2)
    #threshold = max(n,m)
    threshold = hamming_distance + 10

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
            min_costs = min(match, delete, insert)
            
            if min_costs > threshold:
                cost_matrix[i][j] = np.inf
                traceback_matrix[i][j] = 'B'
            else:
                cost_matrix[i][j] = min_costs
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
        logfile.write("###################Cost matrix################\n")
        logfile.write("\n")
        logfile.write("###################Traceback matrix################\n")
        logfile.write(np.array2string(traceback_matrix, threshold=np.inf, max_line_width=np.inf))
        logfile.write("###################Traceback matrix################\n")
    
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

    return cost_matrix[n][m], align1, align2

def main():
    #s = "ATGTTATA"
    #t = "ATCGTCC"
    sequences_file = "./input.txt"
    blosum = read_blosum62("../Data/Lab09/BLOSUM62.txt")
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
