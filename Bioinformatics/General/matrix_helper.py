

def get_profile_matrix(motifs: list[str]) -> list[list[float]]:
    '''
    This function returns a matrix of relative probabilities for each nucleotid in each column.

    Input:
    Matrix as list of strings, each string representing a row in the matrix

    Output:
    List of list of floats, a list of floats representing one column of the profile matrix

    '''
    t = len(motifs)
    k = len(motifs[0])
    profile_matrix = []

    # Iterate over number of cols
    for i in range(k):
        nucleotid_dict = {"A": 0, "C": 0, "G": 0, "T": 0}
        for j in range(t):
            nucelotid = motifs[j][i]
            nucleotid_dict[nucelotid] += 1
        col_list = []
        for key, value in nucleotid_dict.items():
            col_list.append(value / t)
        profile_matrix.append(col_list)
    return profile_matrix


def get_prob_for_kmer(kmer: str, profile_matrix: list[list[float]]) -> float:
    '''
    This function calculates the probability that the given kmer
    does originate from the given profile matrix

    Output:
    Probability as float
    '''
    result_prob = 1.0
    base_order = "ACGT"
    for i in range(len(kmer)):
        char_index = base_order.find(kmer[i])
        result_prob *= profile_matrix[i][char_index]
    return result_prob


def get_most_probable_kmer_for_profile_matrix_in_sequence(sequence: str, k: int, profile_matrix: list[list[float]]) -> str:
    '''
    This function determines the most probable kmer of a sequence given a profile matrix.

    Input:
    Dna sequence which should be checked for possible kmers.
    K as the length of the kmer.
    Profile matrix as a list of list of floats (relative probabilities),
    the inner list representing a column.

    Output:
    Most probable kmer as string.
    '''
    best_kmer = ""
    best_kmer_prob = -1.0

    for i in range(len(sequence) - k + 1):
        current_kmer = sequence[i:i+k]
        kmer_prob = get_prob_for_kmer(current_kmer, profile_matrix)
        if kmer_prob > best_kmer_prob:
            best_kmer_prob = kmer_prob
            best_kmer = current_kmer
    return best_kmer


def get_score_of_motif_matrix(motif_matrix: list[str]):
    '''
    This function calculates the score (better "distance") of a motif matrix.
    The score represents the sum of all differentiating symbols of each column
    that do not match with the most common symbol in this column.
    '''
    score = 0
    k = len(motif_matrix[0])
    t = len(motif_matrix)
    print(f"t is {t}")
    for i in range(k):
        nucleotid_dict = {"A": 0, "C": 0, "G": 0, "T": 0}
        for j in range(t):
            nucleotid = motif_matrix[j][i]
            nucleotid_dict[nucleotid] += 1

        score_of_col = t - max(nucleotid_dict.values())
        score += score_of_col
    return score


def get_consensus_for_motifs(motifs: list[str]):
    profile = get_profile_matrix(motifs)
    base_order = "ACGT"
    consensus = ""
    for i in range(len(profile[0])):
        index_with_highest_prob = profile[i].index(max(profile[i]))
        consensus += base_order[index_with_highest_prob]
    return consensus
