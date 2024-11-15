from Chapter04.Lab04 import subtile_motive
from General.parse_input_files import get_multiple_sequences_from_txt

def calculate_score(motive : list[str]) -> int:
    if len(motive) == 0:
        return 999999
    k = len(motive[0])
    total_score = 0
    # iterate through cols
    for i in range(k):
        occurence_dict = {"A" : 0, "C" : 0, "G" : 0, "T" : 0}
        # iterate through rows
        for j in range(len(motive)):
            # if motive[j][i] in occurence_dict:
            occurence_dict[motive[j][i]] += 1
        
        # calculate score (row length - max val in dict)
        total_score += len(motive) - max(occurence_dict.values())
    return total_score
        

if __name__ == "__main__":
    dna_sequences = get_multiple_sequences_from_txt("../../Data/Algo05_subtiles_motiv_mini.txt")
    # print(dna_sequences)
    scores = dict()
    for k in range(9, 16):
        motives = subtile_motive.find_subtle_motive(dna_sequences, k, 4)
        scores[k] = calculate_score(list(motives))
        if k == 15:
            print(list(motives))
        
    print(f"Minimum score is {min(scores.values())}")
    print(scores)