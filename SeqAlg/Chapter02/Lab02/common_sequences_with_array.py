from Chapter02.Lab02 import kmer_mapping
import math

def reverse_complement(dna_seq):
    complement_dict = {"A": "T", "T" : "A", "G" : "C", "C" : "G", "N" : "N"}
    complementary_seq = ""
    for char in reversed(dna_seq):
        if char.upper() in complement_dict:
            complementary_seq += complement_dict[char.upper()]
    return complementary_seq

def find_common_sequence(text: str, seq_length : int, include_rev_comp = True) -> tuple[set, int]:
    '''
    Finds the most common sequences of length seq_length in text\n
    Returns tuple of the most occuring sequences and the count of occurences
    '''
    res_array = [0] * int(math.pow(4, seq_length))
    maxCount = 0
    common_sequences = set()
    for i in range(0, len(text) - seq_length + 1):
        current_kmer = text[i:i+seq_length]
        kmer_index = kmer_mapping.kmer_to_index(current_kmer)
        res_array[kmer_index] = res_array[kmer_index] + 1
        
        # if sequence was found with same number of occurences than max, add it to res
        if res_array[kmer_index] == maxCount:
            common_sequences.add(current_kmer)
        # if new maxCount is reached, current kmer is only solution
        elif res_array[kmer_index] > maxCount:
            common_sequences = set([current_kmer])
            maxCount = res_array[kmer_index]
        
        # the same for the reverse complement
        if include_rev_comp:
            rev_comp = reverse_complement(current_kmer)
            rev_comp_index = kmer_mapping.kmer_to_index(rev_comp)
            res_array[rev_comp_index] = res_array[rev_comp_index] + 1
            
            if res_array[rev_comp_index] == maxCount:
                common_sequences.add(rev_comp)
            elif res_array[rev_comp_index] > maxCount:
                common_sequences = set([rev_comp])
                maxCount = res_array[rev_comp_index]
            
    return common_sequences, maxCount

def test_cases():
    kmer_length = 4
    res_sequences, num_occurences = find_common_sequence("AGATAATCTG", kmer_length)
    print(f"Most common sequences are: {res_sequences}. The count is {num_occurences}")

if __name__ == "__main__":     
    test_cases()