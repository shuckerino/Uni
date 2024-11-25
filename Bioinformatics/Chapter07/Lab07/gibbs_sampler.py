from General.matrix_helper import get_profile_matrix, get_score_of_motif_matrix, get_random_weighted_kmer_from_sequence
from General.parse_input_files import get_multiple_sequences_from_txt
import random
from tqdm import tqdm

#TODO: make gibbs sampling return median and best score etc. to make it comparable to randomized search
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
        mutated_motif = get_random_weighted_kmer_from_sequence(
            Dna[switched_kmer_idx], profile) # mutated needs to be random -> monte carlo
        motifs = motifs[:switched_kmer_idx] + [mutated_motif] + motifs[switched_kmer_idx+1:] # needs to be inplace

        if get_score_of_motif_matrix(motifs) < get_score_of_motif_matrix(best_motives):
            best_motives = motifs
    return best_motives


if __name__ == "__main__":
    dna = get_multiple_sequences_from_txt(
        "../../Data/Algo04_subtiles_motiv.txt")
    best_motifs = gibbs_sampler(dna, 15, 200)
    score = get_score_of_motif_matrix(best_motifs)
    print(f"Best motifs using gibbs sampling is {best_motifs}")
    print(f"Score is {score}")
    # Gibbs sampling score is between 40 and 50
