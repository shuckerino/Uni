import math
from collections import defaultdict
from General.parse_input_files import get_multiple_sequences_from_txt

def calculate_entropy_for_col(rel_probs : list[float]) -> float:
    '''
    Calculate the entropy value for a single column of relative probabilities.

    Parameters:
    rel_probs (list of float): A list of probabilities that sum to 1.

    Returns:
    float: The entropy value.
    '''
    total_entropy = 0
    for p in rel_probs:
        if p == 0:
            continue
        total_entropy += p * math.log2(p)
    return -1 * total_entropy
    

def calculate_entropy_for_matrix(matrix_profile : list[list[float]]) -> float:
    entropy_of_matrix = 0
    k = len(matrix_profile[0])
    t = len(matrix_profile)
    for c in range(k):
        rel_probs_of_col = []
        for r in range(t):
            rel_probs_of_col.append(matrix_profile[r][c])

        print(f"Rel probs for c = {c}: {rel_probs_of_col}")
        entropy_of_matrix += calculate_entropy_for_col(rel_probs_of_col)
    return entropy_of_matrix
        
def create_profile_of_matrix(matrix : list[str]) -> list[list[float]]:
    '''
    Method for creating a profile of a matrix.
    This profile includes the relative probabilities per column for each base.
    Returns:
    2D list of floats
    '''
    profile_dict = defaultdict(list)
    t = len(matrix)
    k = len(matrix[0])
    for c in range(k):
        base_dict = {"A": 0, "C" : 0, "G" : 0, "T" : 0}
        # count occurences per col
        for r in range(t):
            base_dict[matrix[r][c]] += 1
            
        # add col result to entire profile result
        for key, value in base_dict.items():
            profile_dict[key].append(value / float(t))
            
    profile_result_matrix = [value_list for value_list in profile_dict.values()]
    return profile_result_matrix
            
            
        
if __name__ == "__main__":
    matrix = get_multiple_sequences_from_txt("../../Data/NFKappaB-Matrix.txt")
    matrix = [row.replace(" ", "") for row in matrix]
    # print(f"NFKappaB-Matrix is: {matrix}")
    profile_matrix = create_profile_of_matrix(matrix)
    print(f"Profile of matrix is {profile_matrix}")
    entropy_for_matrix = calculate_entropy_for_matrix(profile_matrix)
    print(f"Entropy of matrix is {entropy_for_matrix}")