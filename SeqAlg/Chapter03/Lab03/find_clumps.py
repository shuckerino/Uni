import parse_text_file
import sys
from collections import defaultdict
sys.path.append('../../Chapter02/Lab02')
import common_sequences_with_array
import kmer_mapping

def find_clumps(sequence : str, k : int, L: int, t) -> dict:
    '''Finding all kmer clumps in sequence\n
       Returns list of kmers, that are (L,t)-clumps in sequence'''
    found_clumps = {} # mapping clump to num of occurences
        
    for i in range(0, len(sequence)):
        print(f"window is {seq}")
        for i in range(0, len(seq) - k): # find all possible kmers in window
            kmer_occurences = common_sequences_with_array.find_common_sequence(seq, k, False)
            print(kmer_occurences)
            # get the indices of the array where the threshold t is succeded
            # all_indices_of_clumps = [kmer_occurences.index(num) for num in kmer_occurences if num >= t]
            # print(all_indices_of_clumps)
            for num in kmer_occurences:
                if num < t:
                    continue                                                        
                kmer = kmer_mapping.index_to_kmer(kmer_occurences.index(num), k)
                print(kmer)
                if kmer in found_clumps:
                    found_clumps[kmer] += 1
                else:
                    found_clumps[kmer] = 1
    return found_clumps
    
def find_clumps_faster(sequence : str, k : int, L: int, t) -> set:
    '''Finding all kmer clumps in sequence\n
       Returns list of kmers, that are (L,t)-clumps in sequence'''
    kmer_to_index_dict = defaultdict(list) # mapping clump to list of indices
    found_clumps = set()
    
    # iterate once over entire sequence and fill kmer_to_index_dict
    for i in range(len(sequence) - k):
        current_kmer = sequence[i:i+k]
        kmer_to_index_dict[current_kmer].append(i)
    
    print([idx_list for idx_list in kmer_to_index_dict.values() if len(idx_list) > 2])
    
    for kmer, index_list in kmer_to_index_dict.items():
        if len(index_list) < t:
            continue
        for i in range(0, len(index_list)):
            if i+t >= len(index_list): # check for out of bounds
                continue
            if index_list[i+t] - index_list[i] <= L: # if difference of indices is smaller than window size
                found_clumps.add(kmer)
    return found_clumps
        
    
if __name__ == "__main__":
    sequence = parse_text_file.get_sequence_from_txt("data/oric_Vibrio_cholerae.txt")
    # sequence = "gatcagcataagggtccCTGCAATGCATGACAAGCCTGCAGTtgttttac".upper()
    print(len(sequence))
    list_of_clumps = find_clumps_faster(sequence, k=9, L=540, t=2)
    print(list_of_clumps)
        