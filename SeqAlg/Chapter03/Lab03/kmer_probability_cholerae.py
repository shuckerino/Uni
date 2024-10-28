import sys
sys.path.append('../../Chapter02/Lab02')
import common_sequences_with_array
import kmer_mapping
import math

def calculate_probability(N, t, k) -> float:
    nenner = float(math.pow(4, (t-1) * k))
    # print(f"nenner is {nenner}")
    zaehler = float(math.comb(N-t*(k-1), k))
    # print(f"zaehler is {zaehler}")
    res = zaehler / nenner
    # print(res)
    return res

if __name__ == "__main__":
    file = open("data/oric_Vibrio_cholerae.txt", "r")
    content = file.readlines()
    sequence = "".join(content).replace('\r', '').replace('\n', '').upper()
    # print(sequence)
    # print(f"length of sequence is {len(sequence)}")
    most_common_kmers = {} #dict mapping kmer to num of occurences
    for k in range(7, 13):
        k_array = common_sequences_with_array.find_common_sequence(sequence, k)
        max_num_of_occurences = max(k_array)
        index_of_most_common_kmer = k_array.index(max_num_of_occurences)
        most_common_kmer = kmer_mapping.index_to_kmer(index_of_most_common_kmer, k)
        most_common_kmers[most_common_kmer] = max_num_of_occurences
        # p = calculate_probability(len(sequence), k, 2)
        # print(calculate_probability(540, 9, 1))
    # print(most_common_kmers)
    for kmer, num in most_common_kmers.items():
        print(f"kmer with probability {calculate_probability(len(sequence), num, len(kmer))}")
    
    
#probability formular:
# Wahrscheinlichkeit, dass kmer in einem Text der Länge N über Alphabet A mindestesns t mal vorkommt
# P(N, A, t, k) = siehe Obsidian