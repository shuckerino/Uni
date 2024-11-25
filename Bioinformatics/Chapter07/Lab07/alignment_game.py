

def play_alignment_game_greedy(v: str, w: str):
    '''
    Align two sequences in a greedy way

    '''
    score = 0
    v_aligned = ""
    w_aligned = ""
    v_pointer = 0
    w_pointer = 0

    while v_pointer < len(v) and w_pointer < len(w):
        if v[v_pointer] == w[w_pointer]:  # match, so plus 1 point
            score += 1
            v_aligned += v[v_pointer]
            w_aligned += w[w_pointer]
            v_pointer += 1
            w_pointer += 1
        else:  # gap or mismatch
            v_aligned += v[v_pointer]
            v_pointer += 1
            w_aligned += "-"

    return v_aligned, w_aligned, score


if __name__ == "__main__":
    w = "ATGCATGCTGCC"
    v = "TGCATGCA"
    v_aligned, w_aligned, score = play_alignment_game_greedy(v, w)
    print(
        f"v aligned is {v_aligned}, w aligned is {w_aligned}. score is {score}")
