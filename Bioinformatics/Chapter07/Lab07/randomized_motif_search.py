from General.matrix_helper import get_profile_matrix, get_most_probable_kmer_for_profile_multi_sequence, get_score_of_motif_matrix
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


def get_median_of_results_for_x_iterations(Dna: list[str], k: int, x: int) -> list[int]:
    list_of_results = []
    for i in tqdm(range(x), "Progress"):
        motifs = randomized_motif_search(Dna, k)
        list_of_results.append(get_score_of_motif_matrix(motifs))
    list_of_results.sort()
    return list_of_results


if __name__ == "__main__":
    dna_sequences = get_multiple_sequences_from_txt(
        "../../Data/Algo04_subtiles_motiv.txt")
    # best_motifs = randomized_motif_search(dna_sequences, 15)
    # print(f"Best motifs are {best_motifs}")

    # for 20, 200 and 2000 the average and median were around 61, the best about 73
    num_iterations = 20
    result_list = get_median_of_results_for_x_iterations(
        dna_sequences, 15, num_iterations)
    print(
        f"Best result of result list for {num_iterations} iterations: {max(result_list)}")
    print(
        f"Median of result list for {num_iterations} iterations: {result_list[len(result_list) // 2]}")
    average = 0
    for val in result_list:
        average += val
    average /= len(result_list)
    print(f"Average of result list for {num_iterations} iterations: {average}")
