from General.matrix_helper import get_profile_matrix, get_score_of_motif_matrix, get_most_probable_kmer_for_profile_matrix_in_sequence
from General.parse_input_files import get_multiple_sequences_from_txt
import random
from tqdm import tqdm


def randomized_motif_search(Dna: list[str], k: int):
    best_motives = []
    motifs = []
    # Init best motifs randomly
    for seq in Dna:
        random_idx = int(random.random() * (len(seq) - k + 1))
        # print(f"Random idx is {random_idx}")
        motifs.append(seq[random_idx:random_idx+k])
    best_motives = motifs

    while True:
        profile = get_profile_matrix(motifs)
        motifs = get_most_probable_kmer_for_profile_multi_sequence(
            Dna, k, profile)
        if get_score_of_motif_matrix(motifs) < get_score_of_motif_matrix(best_motives):
            best_motives = motifs
        else:
            return best_motives


def gibbs_sampler(Dna: list[str], k: int, N: int):
    best_motives = []
    motifs = []
    t = len(Dna)
    # Init best motifs randomly
    for seq in Dna:
        random_idx = int(random.random() * (len(seq)) - k + 1)
        # print(f"Random idx is {random_idx}")
        motifs.append(seq[random_idx:random_idx+k])
    motifs = [m for m in motifs if m != ""]
    best_motives = motifs

    for i in tqdm(range(N), "Progress"):
        switched_kmer_idx = int(random.random() * t)
        motifs = motifs[:switched_kmer_idx] + motifs[switched_kmer_idx+1:]
        profile = get_profile_matrix(motifs)
        mutated_motif = get_most_probable_kmer_for_profile_matrix_in_sequence(
            Dna[switched_kmer_idx], k, profile)
        motifs.append(mutated_motif)

        if get_score_of_motif_matrix(motifs) < get_score_of_motif_matrix(best_motives):
            best_motives = motifs
    return best_motives


if __name__ == "__main__":
    dna = get_multiple_sequences_from_txt(
        "../../Data/Algo04_subtiles_motiv.txt")
    best_motifs = gibbs_sampler(dna, 15, 200)
    score = get_score_of_motif_matrix(best_motifs)
    print(f"Best motifs using gibbs sampling is {score}")
    # Gibbs sampling score is between 40 and 50
