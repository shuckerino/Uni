from Chapter02.Lab02 import kmer_mapping
from General import hamming_distance
from General import parse_input_files
from tqdm import tqdm


def get_min_distance_motif_single_sequence(motif: str, seq: str) -> int:
    k = len(motif)
    min_distance = 9999999
    for i in range(len(seq) - k + 1):
        current_kmer = seq[i:i+k]
        kmer_distance = hamming_distance.calculate_hamming_distance(
            current_kmer, motif)
        if kmer_distance < min_distance:
            min_distance = kmer_distance
    return min_distance


def get_min_distance_motif_multi_sequence(motif: str, list_of_seqs: list[str]) -> int:
    total_sum = 0
    for seq in list_of_seqs:
        total_sum += get_min_distance_motif_single_sequence(motif, seq)
    return total_sum


def get_median_zeichenkette(Dna: list[str], k: int):
    min_found_distance = 9999999
    found_median = None
    for i in tqdm(range(4**k), desc="Processing all possible kmers..."):
        kmer = kmer_mapping.index_to_kmer(i, k)
        kmer_distance = get_min_distance_motif_multi_sequence(kmer, Dna)
        if kmer_distance < min_found_distance:
            min_found_distance = kmer_distance
            found_median = kmer
    return found_median


if __name__ == "__main__":
    dna = parse_input_files.get_multiple_sequences_from_txt(
        "../../Data/Algo04_subtiles_motiv.txt")
    median = get_median_zeichenkette(dna, 7)
    print(f"Found median is {median}")
