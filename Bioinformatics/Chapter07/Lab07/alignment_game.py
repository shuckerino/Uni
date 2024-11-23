from General.parse_input_files import get_multiple_sequences_from_txt


def play_alignment_game(v: str, w: str):

    v_aligned = ""
    w_aligned = ""

    longest_len = len(v)
    if len(w) > longest_len:
        longest_len = len(w)

    for i in range(longest_len):

        # Check if one is empty / out of bounds
        if v[i]
