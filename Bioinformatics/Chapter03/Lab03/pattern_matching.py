import General.parse_input_files as parse_input_files

# idea of pattern matching is similar to find common sequences
# but now we do not save the number of occurences, but the indices instead

def reverse_complement(dna_seq):
    complement_dict = {"A": "T", "T" : "A", "G" : "C", "C" : "G", "N" : "N"}
    complementary_seq = ""
    for char in reversed(dna_seq):
        if char.upper() in complement_dict:
            complementary_seq += complement_dict[char.upper()]
    return complementary_seq

def find_nonamere_in_sequence(seq : str, pattern : str, include_rev_comp = True) -> list[int]:
    '''
    Finding all occurences of pattern in seq
    
    Returns the list of indices, where the pattern occurs in seq
    '''
    k = 9
    seq = seq.upper()
    pattern = pattern.upper()
    found_indices = []
    for i in range(0, len(seq) - k + 1):
        if seq[i:i+k] == pattern:
            found_indices.append(i)
            
        if include_rev_comp:
            rev_comp = reverse_complement(seq[i:i+k])
            if rev_comp == pattern:
                found_indices.append(i)
        
    return found_indices


if __name__ == "__main__":
    text = parse_input_files.get_sequence_from_fasta("../../Data/genom_Vibrio_cholerae.fasta")
    list_of_indices = find_nonamere_in_sequence(text, "ATGATCAAG", False) # wrong ATGATCCAG
    # print(f"Test is {text[116556:116556+9]}")
    print(f"List of indices is {list_of_indices}.")