import kmer_mapping

def reverse_complement(dna_seq):
    complement_dict = {"A": "T", "T" : "A", "G" : "C", "C" : "G", "N" : "N"}
    complementary_seq = ""
    for char in reversed(dna_seq):
        if char.upper() in complement_dict:
            complementary_seq += complement_dict[char.upper()]
    return complementary_seq

def find_common_sequence(text: str, seq_length : int) -> dict:
    res_dict = {} # maps kmer_index to count
    for i in range(0, len(text) - seq_length):
        current_kmer = text[i:i+seq_length]
        # print(current_kmer)
        kmer_index = kmer_mapping.kmer_to_index(current_kmer)
        if kmer_index not in res_dict:
            res_dict[kmer_index] = 1
        else:
            res_dict[kmer_index] = res_dict[kmer_index] + 1
    return res_dict
        
kmer_length = 5
res = find_common_sequence("ACGTACGTACGTTTTAAA", kmer_length)

for key, value in res.items():
    kmer = kmer_mapping.index_to_kmer(key, kmer_length)
    print(f"Kmer {kmer} has count of {value}. Reverse complement is {reverse_complement(kmer)}")