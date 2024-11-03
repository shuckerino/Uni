import sys

def reverse_complement(dna_seq):
    complement_dict = {"A": "T", "T" : "A", "G" : "C", "C" : "G", "N" : "N"}
    complementary_seq = ""
    for char in reversed(dna_seq):
        if char.upper() in complement_dict:
            complementary_seq += complement_dict[char.upper()]
    return complementary_seq

if len(sys.argv) == 1:
    print("Please provide dna sequence(s) as argument(s)")

for i in range(1, len(sys.argv)):
    print(f"Complementary reversed dna sequence is: {reverse_complement(sys.argv[i])}")