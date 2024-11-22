from General.matrix_helper import get_profile_matrix, get_most_probable_kmer_for_profile_matrix_in_sequence, get_score_of_motif_matrix, get_consensus_for_motifs
from General.parse_input_files import get_multiple_sequences_from_txt
from tqdm import tqdm


def MotivSucheGreedy(Dna, k):
    t = len(Dna)
    best_motives = []
    besteDistanz = 99999999

    # Initialize best motives with first kmer of each sequence in Dna
    for i in range(len(Dna)):
        best_motives.append(Dna[i][:k])

    # Iterate over first Dna sequence
    for j in range(len(Dna[0]) - k + 1):
        motiv1 = Dna[0][j:j+k]
        motives = [motiv1]
        for i in range(1, t):  # iterate from 2 to t
            # print(f"Trying to get profile for {motives}")
            profile = get_profile_matrix(motives)
            best_fit = get_most_probable_kmer_for_profile_matrix_in_sequence(
                Dna[i], k, profile)
            motives.append(best_fit)
        # print(f"Motives are {motives}")
        d = get_score_of_motif_matrix(motives)
        if d < besteDistanz:
            besteDistanz = d
            best_motives = motives
    return best_motives


if __name__ == "__main__":
    dna_sequences = get_multiple_sequences_from_txt(
        "../../Data/Algo04_subtiles_motiv.txt")
    best_motives = MotivSucheGreedy(dna_sequences, 15)
    consensus = get_consensus_for_motifs(best_motives)
    score = get_score_of_motif_matrix(best_motives)
    print(f"Best motives are {best_motives}")
    print(f"Consensus of best motives is {consensus}")
    print(f"Score of best motives is {score}")
