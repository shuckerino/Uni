import numpy as np
#from timeit import default_timer as timer

# maps line number in input file to path for log file (best case, worst case, average case)
case_dict = {1 : "logs/best_case_log.txt",
             5: "logs/worst_case_log.txt",
             9: "logs/average_case_log.txt"}

def calculate_hamming_distance(pattern : str, neighbour : str) -> int:
    hamming_distance = 0
    min_len = min(len(pattern), len(neighbour))
    for i in range(0, min_len):
        if pattern[i] != neighbour[i]:
            hamming_distance += 1
            
    return hamming_distance

def cost(a, b):
    if a == b:
        return 0  # Match
    return 1  # Mismatch

def read_sequences(file_path, line_num):
    """Reads sequences from a file."""
    with open(file_path, 'r') as file:
        sequences = file.readlines()
    return sequences[line_num].strip(), sequences[line_num + 1].strip()

def global_alignment_bb(seq1, seq2, logfile_path, with_bb = False):
    
    def log_results(filepath):
        with open(filepath, "w") as logfile:
            logfile.write("###################Heuristics################\n")
            logfile.write(f"Patterns {seq1} and {seq2}\n")
            logfile.write(f"Expected costs: {upper_threshold}\n")
            logfile.write(f"Actual costs: {cost_matrix[n][m]}\n")
            logfile.write(f"Number of total iterations: {num_total_iterations}\n")
            logfile.write(f"Number of branch and bounds: {num_bb}\n")
            logfile.write(f"Iterations saved in %: {num_bb / num_total_iterations}\n")
            logfile.write(f"Number of threshold calculations: {num_threshold_calculations}\n")
            logfile.write(f"Number of threshold changes: {num_threshold_changes}\n")
            logfile.write(f"Found Alignment:\n")
            logfile.write(f"{align1}\n")
            logfile.write(f"{align2}\n")
            logfile.write("\n###################Cost matrix################\n")
            logfile.write(np.array2string(cost_matrix, threshold=np.inf, max_line_width=np.inf))
            logfile.write("\n###################Cost matrix################\n")
            logfile.write("\n")
            logfile.write("\n###################Traceback matrix################\n")
            logfile.write(np.array2string(traceback_matrix, threshold=np.inf, max_line_width=np.inf))
            logfile.write("\n###################Traceback matrix################\n")
    
    num_bb = 0
    num_total_iterations = 0
    num_matches = 0
    num_threshold_changes = 0
    num_threshold_calculations = 0
    n = len(seq1)
    m = len(seq2)
    gap_costs = 1
    hamming_distance = calculate_hamming_distance(seq1, seq2)
    
    # estimate the costs
    upper_threshold = (hamming_distance + abs(n - m)) * cost("a", "b")

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
    
    # Calculate base modulo (important for dynamic update of our branch and bound heuristic)
    total_cells = n * m
    # Define base modulo dependent on input length of sequences
    base_modulo = max(1, total_cells // max(n, m))
    # Define base modulo as static size
    #base_modulo = max(1, total_cells // 100000000000)
    
    # Fill in the scoring matrix and traceback matrix
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            num_total_iterations += 1          
            
            match_cost = cost(seq1[i - 1], seq2[j - 1])
            match = cost_matrix[i - 1][j - 1] + match_cost
            delete = cost_matrix[i - 1][j] + gap_costs
            insert = cost_matrix[i][j - 1] + gap_costs
            #print(f"Match cost: {match}, Delete cost: {delete}, Insert cost: {insert}")
            current_costs = min(match, delete, insert)
            
            # Dynamically adjust progress
            progress = num_total_iterations / total_cells
            dynamic_modulo = max(1, int(base_modulo * (1 + progress)))

            if with_bb and num_total_iterations > 0 and num_total_iterations < (n*m - 5) and num_total_iterations % dynamic_modulo == 0:
                num_threshold_calculations += 1
                remaining_costs = (calculate_hamming_distance(seq1[i:], seq2[j:]) + abs((n - i) - (m - j))) * cost("a", "b")
                max_costs_up_to_here = max(cost_matrix[i - 1][j - 1], cost_matrix[i][j - 1], cost_matrix[i - 1][j]) # get max of ingoing edges
                new_upper_threshold = max_costs_up_to_here + remaining_costs
                if new_upper_threshold < upper_threshold:
                    num_threshold_changes += 1
                    upper_threshold = new_upper_threshold
                    #print(f"Lowered threshold to {upper_threshold}")
            
            # If the total costs until now are already higher than our expected cost, branch
            if with_bb and current_costs > upper_threshold:
                num_bb += 1
                cost_matrix[i][j] = np.inf
                traceback_matrix[i][j] = 'B'
            else:
                cost_matrix[i][j] = current_costs
                # Mark cell for backtracking
                if cost_matrix[i][j] == match:
                    traceback_matrix[i][j] = 'D'  # Diagonal
                    num_matches += 1
                elif cost_matrix[i][j] == delete:
                    traceback_matrix[i][j] = 'U'  # Up
                else:
                    traceback_matrix[i][j] = 'L'  # Left
                    
            #threshold = min(threshold, min_costs)
               
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

    
    log_results(logfile_path)


    return cost_matrix[n][m], align1, align2

def main():
    sequences_file = "./input.txt"
    
    for line_num, log_path in case_dict.items():
        print(f"####Case: {log_path.split(".")[0]}####")
        s, t = read_sequences(sequences_file, line_num)
        print(f"s is {s}")
        print(f"t is {t}")
        
        #start = timer()  # depends on package
        result_costs, alignment1, alignment2 = global_alignment_bb(s, t, log_path, True)
        #end = timer()
        #print(f"Time took in s: {end - start}\n")
        print(f"Alignment costs: {result_costs}")
        print(f"Best found alignments:\n")
        print(alignment1)
        print(alignment2)

if __name__ == "__main__":
    main()
