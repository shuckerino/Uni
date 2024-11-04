from collections import defaultdict

base_order = "ACGT"

# What is subtile motive problem?
# - find all kmers with max mismatch of d that occur in all given dna strands


# Solution
# - iterate over first dna sequence and save all kmers and possible neighbours with max mismatch of d
# - iterate 

# save in dict kmer to neighhbours

#TODO: doppelter Abstand ist doch erlaubt! also siehe pseudocode, wir müssen doppelte nachbarschaft berechnen

def get_neighbours_with_max_mismatches(pattern : str, d : int) -> set[str]:
    
    def recursive_neighbour(current_pattern : str, left_mismatches : int, index : int):
        
        # base case: no mismatches allowed or end of pattern
        if left_mismatches == 0 or index == len(pattern):
            all_neighbours.add(current_pattern)
            return
        
        # add current pattern without any changes
        all_neighbours.add(current_pattern)
        
        # get all combinations with all possible mismatches at this position
        for i in range(index, len(pattern)):
            for base in base_order:
                if pattern[i] != base:
                    # replace current character and call recursive function again
                    mutated_pattern  = current_pattern[:i] + base + current_pattern[i+1:]
                    recursive_neighbour(mutated_pattern, left_mismatches - 1, i+1)
    
    all_neighbours = set()
    recursive_neighbour(pattern, d, 0)
    return all_neighbours

def find_subtle_motive(list_of_sequences : list[str], k : int, d : int) -> set[str]:
    if len(list_of_sequences) == 0:
        raise ValueError("The list of sequences cannot be empty")
        
    dict_of_first_sequence = find_all_motives_in_single_sequence(list_of_sequences[0], k, d)
    
    all_subtle_motives_candidates = set() # set of key kmers
    
    # find matches in second sequence
    # TODO: check if even 2 sequences
    second_sequence = list_of_sequences[1]
    for j in range(len(second_sequence)):
        current_kmer = second_sequence[j:j+k]
            
        # now check if current_kmer has any match
        if current_kmer in dict_of_first_sequence:
            all_subtle_motives_candidates.add(current_kmer)
            
        # now check for inexact matches
        for key_kmer, neighbours in dict_of_first_sequence.items():
            if current_kmer in neighbours:
                all_subtle_motives_candidates.add(key_kmer)
    
    # iterate through rest of sequences
    for i in range(2, len(list_of_sequences)):
        candidates_also_in_this_sequence = set()
        current_sequence = list_of_sequences[i]
        for j in range(len(current_sequence)):
            current_kmer = current_sequence[j:j+k]
            for kmer in all_subtle_motives_candidates:
                if current_kmer in dict_of_first_sequence[kmer]:
                    candidates_also_in_this_sequence.add(kmer)
                    
        # schnittmenge der sets bilden
        all_subtle_motives_candidates.intersection_update(candidates_also_in_this_sequence)
        if len(all_subtle_motives_candidates) == 0:
            print("No subtle motives found")
            return set()
        
                
    return all_subtle_motives_candidates       
    

def find_all_motives_in_single_sequence(sequence: str, k : int, d : int) -> set[str]:
    
    kmer_to_neighbours_dict = defaultdict(set)
    for i in range(0, len(sequence) - k + 1):
        current_kmer = sequence[i:i+k]
        
        # find all neighbours of kmer with max d mismatches
        neighbours = get_neighbours_with_max_mismatches(current_kmer, d)

        kmer_to_neighbours_dict[current_kmer] |= neighbours

    return kmer_to_neighbours_dict
        


if __name__ == "__main__":
    # print(get_neighbours_with_max_mismatches("ATTA", 0))
    dna_sequences = []
    with open("../../Data/Algo04_subtiles_motiv.txt", "r") as file:
        dna_sequences = file.readlines()
        dna_sequences = [seq.strip() for seq in dna_sequences]
        
    all_motives = find_subtle_motive(dna_sequences, 9, 4)
    print(len(all_motives))
    print(all_motives)