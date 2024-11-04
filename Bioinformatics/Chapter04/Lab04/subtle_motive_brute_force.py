base_order = "ACGT"

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

def find_subtle_motive(list_of_dna_sequences : list[str], k : int, d : int) -> set[str]:
    patterns = set()
    # iterate over all kmers in all dna sequences
    for seq in list_of_dna_sequences:
        for i in range(len(seq) - k + 1):
            current_kmer = seq[i:i+k]
            neighbours = get_neighbours_with_max_mismatches(current_kmer, d)
            for nb in neighbours:
                # check if neighbour is in all dna sequences
                nb_is_in_all_sequences = True
                for subseq in list_of_dna_sequences:
                    if subseq.find(nb) == -1:
                        nb_is_in_all_sequences = False
                        break
                if nb_is_in_all_sequences:
                    patterns.add(nb)
    return patterns

if __name__ == "__main__":
    dna_sequences = []
    with open("../../Data/Algo04_subtiles_motiv.txt", "r") as file:
        dna_sequences = file.readlines()
        dna_sequences = [seq.strip() for seq in dna_sequences]
        
    all_motives = find_subtle_motive(dna_sequences, 9, 4)
    print(len(all_motives))
    print(all_motives)