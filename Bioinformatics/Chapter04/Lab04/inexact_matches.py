from General import parse_input_files
from Chapter02.Lab02 import common_sequences_with_array, kmer_mapping
import math

base_order = "ACGT"

def get_immediate_neighbours(pattern: str) -> set[str]:
    '''Get all patterns that have one mismatch at most'''
    result_set = {pattern}  # pattern is neighbour itself
    for i in range(0, len(pattern)):
        for mismatch in base_order:
            if mismatch == pattern[i]:
                continue
            neighbour = pattern[:i] + mismatch + pattern[i+1:]
            result_set.add(neighbour)
    return result_set

def calculate_hamming_distance(pattern : str, neighbour : str) -> int:
    '''Compare two patterns of same length and return their hamming distance'''
    if len(pattern) != len(neighbour):
        return -1
    hamming_distance = 0
    for i in range(0, len(pattern)):
        if pattern[i] != neighbour[i]:
            hamming_distance += 1
            
    return hamming_distance

def find_common_sequence_with_neighbours(text: str, seq_length : int, include_rev_comp = True) -> tuple[set, int]:
    '''
    Finds the most common sequences of length seq_length in text with neighbours\n
    Returns tuple of the most occuring sequences and the count of occurences
    '''
    res_array = [0] * int(math.pow(4, seq_length))
    for i in range(0, len(text) - seq_length + 1):
        current_kmer = text[i:i+seq_length]
        
        # find all neighbours of kmer, if hamming_distance <= 1 -> increase count of neighbour
        neighbours = get_immediate_neighbours(current_kmer)
        for n in neighbours:
            neighbour_index = kmer_mapping.kmer_to_index(n)
            res_array[neighbour_index] = res_array[neighbour_index] + 1
        
        # the same for the reverse complement
        if include_rev_comp:
            rev_comp = common_sequences_with_array.reverse_complement(current_kmer)
            
            # find all neighbours of rev_comp, if hamming_distance <= 1 -> increase count of neighbour
            neighbours = get_immediate_neighbours(rev_comp)
            for n in neighbours:
                neighbour_index = kmer_mapping.kmer_to_index(n)
                res_array[neighbour_index] = res_array[neighbour_index] + 1
                    
    # find max
    maxCount = 0
    common_sequences = set()
    for i in range(len(res_array)):
        if res_array[i] == 0:
            continue
        if res_array[i] == maxCount:
            kmer = kmer_mapping.index_to_kmer(i, 9)
            common_sequences.add(kmer)
        elif res_array[i] > maxCount:
            kmer = kmer_mapping.index_to_kmer(i, 9)
            common_sequences = set([kmer])
            maxCount = res_array[i]
        
    return common_sequences, maxCount

if __name__ == "__main__":
    complete_seq = parse_input_files.get_sequence_from_fasta("../../Data/genom_Escherichia_coli.fasta")
    cutted_seq = complete_seq[3923620:3923620+500]
    common_kmers, count = find_common_sequence_with_neighbours(cutted_seq, 9, True)
    print(count)
    print(common_kmers)