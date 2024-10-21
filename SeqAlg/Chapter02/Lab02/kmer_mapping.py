import math

base_order = "ACGT"

def kmer_to_index(kmer : str) -> int:
    '''Returns the index of the passed kmer'''
    # per row are 4^k entries
    res_idx = 0
    for idx, base in enumerate(kmer):
        index_constant = math.pow(4, len(kmer) - idx - 1)
        res_idx += index_constant * base_order.index(base)
    return int(res_idx)

def index_to_kmer(index: int, k: int) -> str:
    '''Returns the kmer for a given index'''
    kmer = ""
    for i in range(k):
        # Find the corresponding base for the current position
        base_idx = index % 4  # get the remainder (current base index)
        kmer = base_order[base_idx] + kmer  # prepend to build the kmer from the end
        index //= 4  # update the index for the next position
    return kmer

if __name__ == "__main__":
    print(kmer_to_index("GCGTAA"))
    print(index_to_kmer(2480, 6))
    # print(kmer_to_index("CG"))
    # print(kmer_to_index("AAC"))
    # print(kmer_to_index("AAG"))
    # print(kmer_to_index("AAT"))
    # print(kmer_to_index("TTT"))
    # print(kmer_to_index("CC"))
    # print(kmer_to_index("GT"))
    # print(kmer_to_index("ATCT"))
    # print(index_to_kmer(6, 2))

