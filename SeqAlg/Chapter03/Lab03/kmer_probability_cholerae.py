import sys
sys.path.append('../../Chapter02/Lab02')
import common_sequences_with_array
import kmer_mapping

if __name__ == "__main__":
    file = open("data/oric_Vibrio_cholerae.txt", "r")
    content = file.readlines()
    sequence = "".join(content).replace('\r', '').replace('\n', '').upper()
    # print(sequence)
    # print(f"length of sequence is {len(sequence)}")
    most_common_kmers = []
    for k in range(7, 13):
        k_array = common_sequences_with_array.find_common_sequence(sequence, k)
        index_of_most_common_kmer = k_array.index(max(k_array))
        most_common_kmer = kmer_mapping.index_to_kmer(index_of_most_common_kmer, k)
        most_common_kmers.append(most_common_kmer)
    print(most_common_kmers)