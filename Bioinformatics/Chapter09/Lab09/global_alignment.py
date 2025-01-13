import numpy as np

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

def read_sequences(file_path):
    """Reads sequences from a file."""
    with open(file_path, 'r') as file:
        sequences = file.readlines()
    #return "ATGTTATA", "ATCGTCC"
    return sequences[1].strip(), sequences[2].strip()

def needleman_wunsch(seq1, seq2, blosum62, gap_penalty):
    """Performs the Needleman-Wunsch global alignment algorithm."""
    n = len(seq1)
    m = len(seq2)

    # Initialize the scoring matrix and traceback matrix
    score_matrix = np.zeros((n + 1, m + 1), dtype=int)
    traceback_matrix = np.zeros((n + 1, m + 1), dtype=str)

    # Initialize the first row and column
    for i in range(1, n + 1):
        score_matrix[i][0] = i * gap_penalty
        traceback_matrix[i][0] = 'U'  # Up

    for j in range(1, m + 1):
        score_matrix[0][j] = j * gap_penalty
        traceback_matrix[0][j] = 'L'  # Left

    # Fill in the scoring matrix and traceback matrix
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            match_score = blosum62[seq1[i - 1]][seq2[j - 1]]
            match = score_matrix[i - 1][j - 1] + match_score
            delete = score_matrix[i - 1][j] + gap_penalty
            insert = score_matrix[i][j - 1] + gap_penalty

            score_matrix[i][j] = max(match, delete, insert)

            if score_matrix[i][j] == match:
                traceback_matrix[i][j] = 'D'  # Diagonal
            elif score_matrix[i][j] == delete:
                traceback_matrix[i][j] = 'U'  # Up
            else:
                traceback_matrix[i][j] = 'L'  # Left

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

    return score_matrix[n][m], align1, align2

def main():
    # File paths
    blosum_file = "../../Data/Lab09/BLOSUM62.txt"
    sequences_file = "../../Data/Lab09/global_alignment.txt"

    # Read BLOSUM62 and sequences
    blosum62 = read_blosum62(blosum_file)
    seq1, seq2 = read_sequences(sequences_file)

    # Gap penalty
    gap_penalty = -5

    # Perform global alignment
    score, alignment1, alignment2 = needleman_wunsch(seq1, seq2, blosum62, gap_penalty)

    # Output the results
    print(score)
    print(alignment1)
    print(alignment2)

if __name__ == "__main__":
    main()

'''
BLOSUM -> je höher der Wert, desto ähnlicher
PAM -> je höher der Wert, desto distanter

'''