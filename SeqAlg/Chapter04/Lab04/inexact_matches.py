base_order = "ACGT"

from General import parse_input_files

def get_immediate_neighbours(pattern: str) -> set[str]:
    '''Get all patterns that have one mismatch at most'''
    result_set = set(pattern) # pattern is neighbour itself
    for i in range(0, len(pattern)):
        for mismatch in base_order:
            if mismatch == pattern[i]:
                continue
            neighbour = pattern[:i] + mismatch + pattern[i+1:]
            result_set.add(neighbour)
    return result_set
            

if __name__ == "__main__":
    
    print(get_immediate_neighbours("A"))