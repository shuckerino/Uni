import General.parse_input_files as parse_input_files
from collections import defaultdict

def find_clumps_faster(sequence : str, k : int, L: int, t) -> set:
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
        
    
if __name__ == "__main__":
    # sequence = parse_input_files.get_sequence_from_txt("data/oric_Vibrio_cholerae.txt")
    sequence = parse_input_files.get_sequence_from_fasta("../../Data/genom_Vibrio_cholerae.fasta")
    # sequence = "gatcagcataagggtccCTGCAATGCATGACAAGCCTGCAGTtgttttac".upper()
    # print(len(sequence))
    list_of_clumps = find_clumps_faster(sequence, k=9, L=540, t=6) # t = 6, L = len(oriC)
    print(list_of_clumps)
        