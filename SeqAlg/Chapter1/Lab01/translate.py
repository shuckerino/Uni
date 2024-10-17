import sys

def get_dna_seq_from_rna(rna : str) -> str:
    return rna.replace("U", "T").replace("u", "t")

def read_protein_dict_from_file() -> dict:
    protein_dict = {}
    file = open("protein_sequences.csv", "r")
    for line in file.read().split("\n"):
        line_args = line.split(",")
        if len(line_args) > 1:
            if line_args[1] == "O": # encode stop codon with '*'
                protein_dict[line_args[0]] = "*"
            else:
                protein_dict[line_args[0]] = line_args[1]
    return protein_dict
    

def translate(rna : str) -> str:
    res = ""
    dna_seq = get_dna_seq_from_rna(rna)
    protein_dict = read_protein_dict_from_file()
    # print(protein_dict)
    seqs_to_check = [dna_seq[i:i+3] for i in range(0, len(dna_seq), 3)]
    # print(seqs_to_check)
    for seq in seqs_to_check:
        if seq in protein_dict:
            res += protein_dict[seq]
    return res
 
if len(sys.argv) == 1:
    print("Please provide filename for test cases!")
    exit(1)

test_case_file = sys.argv[1]

with open(test_case_file, "r") as file:
    for test_case in file:
        test_seq = test_case.strip()
        print(f"Protein sequence for {test_seq}: {translate(test_seq)}")