iupac_dict = { "A" : "A", "T" : "T", "G" : "G", "C" : "C", "AT" : "W", 
                  "CG" : "S",
                  "AC" : "M",
                  "GT" : "K",
                  "AG" : "R",
                  "CT" : ["Y"],
                  "ACGT" : "N"}

def encode_sequences(iupac_tuple : tuple) -> str:
    iupac_res = ""
    length = len(str(tuple[0]))
    
    for i in range(length):
        symbol_set = set()
        for j in range(len(iupac_tuple)):
            current_symbol = iupac_tuple[j][i]
            symbol_set.add(current_symbol)
        symbols = "".join(sorted(symbol_set))
        iupac_res += iupac_dict[symbols]
    return iupac_res

test_tuple = ("AGGCCA", "AGGCCT")
print(encode_sequences(test_tuple))