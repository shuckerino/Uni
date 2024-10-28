from collections import defaultdict

# idea is similar to find common sequences, but now we do not save the number of occurences, but the indices instead
# TODO pass muster as argument
def reverse_complement(dna_seq):
    complement_dict = {"A": "T", "T" : "A", "G" : "C", "C" : "G", "N" : "N"}
    complementary_seq = ""
    for char in reversed(dna_seq):
        if char.upper() in complement_dict:
            complementary_seq += complement_dict[char.upper()]
    return complementary_seq

def read_fasta_file(filename : str) -> str:
    with open(filename, "r") as fasta_file:
        file_without_header = fasta_file.read().splitlines()[1:]
        return "".join(file_without_header)

def find_nonamere_in_sequence(seq : str):
    k = 9
    seq = seq.upper()
    nonamere_occurences = defaultdict(list) # dict mapping nonamere to list of indices
    for i in range(0, len(seq) - k + 1):
        current_nonamere = seq[i:i+k]
        rev_comp = reverse_complement(current_nonamere)
        # print(current_nonamere)
        if current_nonamere in nonamere_occurences:
            nonamere_occurences[current_nonamere].append(i)
        else:
            nonamere_occurences[current_nonamere] = [i]
            
        if rev_comp in nonamere_occurences:
            nonamere_occurences[rev_comp].append(i)
        else:
            nonamere_occurences[rev_comp] = [i]
            
    largest_key = max(nonamere_occurences, key=lambda k: len(nonamere_occurences[k]))
    largest_list = nonamere_occurences[largest_key]
    return largest_key, largest_list


if __name__ == "__main__":
    # res = find_nonamere_in_sequence("atcaatgatcaacgtaagcttctaagcATGATCAAGgtgctcacacagtttatccacaacctgagtggatgacatcaagataggtcgttgtatctccttcctctcgtactctcatgaccacggaaagATGATCAAGagaggatgatttcttggccatatcgcaatgaatacttgtgacttgtgcttccaattgacatcttcagcgccatattgcgctggccaaggtgacggagcgggattacgaaagcatgatcatggctgttgttctgtttatcttgttttgactgagacttgttaggatagacggtttttcatcactgactagccaaagccttactctgcctgacatcgaccgtaaattgataatgaatttacatgcttccgcgacgatttacctCTTGATCATcgatccgattgaagatcttcaattgttaattctcttgcctcgactcatagccatgatgagctCTTGATCATgtttccttaaccctctattttttacggaagaATGATCAAGctgctgctCTTGATCATcgtttc")
    # print(res)
    text = read_fasta_file("data/genom_Vibrio_cholerae.fasta")
    # print(text)
    nonamere, list_of_indices = find_nonamere_in_sequence(text)
    print(f"Most common nonamere is {nonamere} with {len(list_of_indices)} occurences.")
    print(f"List of indices is {list_of_indices}.")