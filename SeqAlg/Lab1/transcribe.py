import sys

def transcribe_from_sense_strand(dna_seq):
    '''only replace thymin with uracil'''
    return dna_seq.replace('T', 'U').replace('t', 'u')

def transcribe_from_antisense_strand(dna_seq):
    complement_dict = {"A": "U", "T" : "A", "G" : "C", "C" : "G"}
    rna_seq = ""
    for char in dna_seq:
        if char.upper() in complement_dict:
            rna_seq += complement_dict[char.upper()]
    return rna_seq

if len(sys.argv) == 1:
    print("Please provide dna sequence(s) as argument(s)")
    
for i in range(1, len(sys.argv)):
    print(f"RNA of sense strand: {transcribe_from_sense_strand(sys.argv[i])}")
    print(f"RNA of antisense strand: {transcribe_from_antisense_strand(sys.argv[i])}")


