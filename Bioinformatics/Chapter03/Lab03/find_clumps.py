import General.parse_input_files as parse_input_files
from collections import defaultdict

def find_clumps_faster(sequence : str, k : int, L: int, t : int) -> set[str]:
    '''Finding all kmer clumps in sequence\n
       Returns list of kmers, that are (L,t)-clumps in sequence'''
    kmer_to_index_dict = defaultdict(list) # mapping clump to list of indices
    found_clumps = set()
    
    # iterate once over entire sequence and fill kmer_to_index_dict
    for i in range(len(sequence) - k):
        current_kmer = sequence[i:i+k]
        kmer_to_index_dict[current_kmer].append(i)
    
    # print([idx_list for idx_list in kmer_to_index_dict.values() if len(idx_list) > 2])
    
    for kmer, index_list in kmer_to_index_dict.items():
        if len(index_list) < t:
            continue
        for i in range(0, len(index_list)):
            if i+t >= len(index_list): # check for out of bounds
                continue
            if index_list[i+t] - index_list[i] <= L: # if difference of indices is smaller than window size
                found_clumps.add(kmer)
    return found_clumps

def find_clumps_with_window(sequence : str, k : int, L : int, t : int) -> set[str]:
    '''
    We know want to only view the difference to the previous window
    '''
    found_clumps = set()
    kmer_to_count_dict = dict()
    
    #get kmers of first_window
    first_window = sequence[:L]
    for i in range(len(first_window) - k + 1):
        current_kmer = first_window[i:i+k]
        if current_kmer in kmer_to_count_dict and current_kmer not in found_clumps: # ignore if already found
            kmer_to_count_dict[current_kmer] += 1
            if kmer_to_count_dict[current_kmer] >= t:
                found_clumps.add(current_kmer)
        else:
            kmer_to_count_dict[current_kmer] = 1
    
    # print(f"kmer dict is {kmer_to_count_dict}")
    
    # iterare through the rest of windows
    for i in range(1, len(sequence) - L):
        window_L = sequence[i:i+L]
        # print(f"window l is {window_L}")
    
        # update dict by removing element before
        dropped_kmer = sequence[i-1:i-1+k]
        # print(f"dropped kmer is {dropped_kmer}")
        if dropped_kmer in kmer_to_count_dict:
            kmer_to_count_dict[dropped_kmer] -= 1
            if kmer_to_count_dict[dropped_kmer] == 0:
                _ = kmer_to_count_dict.pop(dropped_kmer)
        
        # update dict by adding new element
        new_kmer = window_L[L - k:]
        if new_kmer in kmer_to_count_dict and new_kmer not in found_clumps: # ignore if already found
            kmer_to_count_dict[new_kmer] += 1
            if kmer_to_count_dict[new_kmer] >= t:
                found_clumps.add(new_kmer)
                
    return found_clumps
    
        
    
if __name__ == "__main__":
    # sequence = parse_input_files.get_sequence_from_txt("data/oric_Vibrio_cholerae.txt")
    sequence = parse_input_files.get_sequence_from_fasta("../../Data/genom_Vibrio_cholerae.fasta")
    # sequence = "gatcagcataagggtccCTGCAATGCATGACAAGCCTGCAGTtgttttac".upper()
    # print(len(sequence))
    list_of_clumps = find_clumps_faster(sequence, k=9, L=540, t=6) # t = 6, L = len(oriC)
    print(list_of_clumps)
    
    print(50 * "#")
    
    list_of_clumps = find_clumps_with_window(sequence, k=9, L=540, t=1) # t = 6, L = len(oriC)
    print(list_of_clumps)
        