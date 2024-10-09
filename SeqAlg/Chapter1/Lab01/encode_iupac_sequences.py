
def encode_sequences(iupac_tuple : tuple) -> str:
    dna_seq1, dna_seq2 = iupac_tuple[0], iupac_tuple[1]
    iupac_res = ""
    for i in range(len(dna_seq1)):
        if dna_seq1[i] == dna_seq2[i]:
            iupac_res += dna_seq1[i]
        else:
            iupac_res += get_possible_iupac_symbol(dna_seq1[i], dna_seq2[i])
    return iupac_res
        
def get_possible_iupac_symbol(base1 : str, base2: str) -> str:
   if base1 == "A" and base2 == "T":
       return "W"
   if base1 == "C" and base2 == "G":
       return "S"
   if base1 == "A" and base2 == "C":
       return "M"
   if base1 == "G" and base2 == "T":
       return "K"
   if base1 == "A" and base2 == "G":
       return "R"
   if base1 == "C" and base2 == "T":
       return "Y"
   return "N"
   

    

print(encode_sequences(("AGGCCA", "AGGCCT")))
