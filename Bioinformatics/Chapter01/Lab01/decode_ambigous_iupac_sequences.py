import sys

iupac_dict = {"W" : ["A", "T"], 
                  "S" : ["C", "G"],
                  "M" : ["A", "C"],
                  "K" : ["G", "T"],
                  "R" : ["A", "G"],
                  "Y" : ["C", "T"],
                  "N" : ["A", "G", "C", "T"]}

res = []

def enumerate_sequences(iupac_sequence: str, current_sequence: str = ""):
    
    if len(iupac_sequence) == 0:
        res.append(current_sequence)
        return res
    
    current_char = iupac_sequence[0].upper()
    
    if current_char in iupac_dict:
        for val in iupac_dict[current_char]:
            # Recursive call with the next character and the new sequence
            enumerate_sequences(iupac_sequence[1:], current_sequence + val)
    else:
        # If it's a normal base, just add it to the current sequence
        enumerate_sequences(iupac_sequence[1:], current_sequence + current_char)
        
    return res

if len(sys.argv) == 1:
    print("Please provide iupac sequence(s) as argument(s)")

for i in range(1, len(sys.argv)):
    print(f"Possible sequences are: {enumerate_sequences(sys.argv[i])}")
        