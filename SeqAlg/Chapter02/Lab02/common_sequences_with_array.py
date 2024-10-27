import kmer_mapping
import math

def reverse_complement(dna_seq):
    complement_dict = {"A": "T", "T" : "A", "G" : "C", "C" : "G", "N" : "N"}
    complementary_seq = ""
    for char in reversed(dna_seq):
        if char.upper() in complement_dict:
            complementary_seq += complement_dict[char.upper()]
    return complementary_seq

def find_common_sequence(text: str, seq_length : int, include_rev_comp = True) -> list:
    # res_dict = {} # maps kmer_index to count
    res_array = [0] * int(math.pow(4, seq_length))
    for i in range(0, len(text) - seq_length):
        current_kmer = text[i:i+seq_length]
        kmer_index = kmer_mapping.kmer_to_index(current_kmer)
        res_array[kmer_index] = res_array[kmer_index] + 1
        
        if include_rev_comp:
            rev_comp = reverse_complement(current_kmer)
            # print(current_kmer)
            rev_comp_index = kmer_mapping.kmer_to_index(rev_comp)
            res_array[rev_comp_index] = res_array[rev_comp_index] + 1
    return res_array

def test_cases():
    kmer_length = 3
    # res = find_common_sequence("ACGTACGTACGTTTTAAA", kmer_length)
    res = find_common_sequence("AGATAATCTG", kmer_length)

    for i in range(0, len(res)):
        if res[i] == 0:
            continue
        kmer = kmer_mapping.index_to_kmer(i, kmer_length)
        print(f"Kmer {kmer} has count of {res[i]}")

if __name__ == "__main__":     
    test_cases()