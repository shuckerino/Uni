import sys
import parse_input_files
from Chapter02.Lab02 import common_sequences_with_array
import math

def calculate_probability(N: int, t : int, k : int) -> float:
    return (math.comb(N-t * (k-1), t)) / (4 ** ((t-1) * k))

if __name__ == "__main__":
    sequence = parse_input_files.get_sequence_from_txt("data/oric_Vibrio_cholerae.txt")

    for k in range(7, 13):
        common_sequences, num_occurences = common_sequences_with_array.find_common_sequence(sequence, k)
        
        for seq in common_sequences:
            print(f"Common {k}-mer is {seq} with {num_occurences} occurences. Probability for that is {calculate_probability(len(sequence), num_occurences, k)}")