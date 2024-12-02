

def lcs_backtrack(v, w):
    cols = len(v) + 1
    rows = len(w) + 1
    s = [[0 for i in range(cols)] for _ in range(rows)]
    backtrack_result = [["" for _ in range(cols)] for _ in range(rows)]

    for i in range(1, rows):
        for j in range(1, cols):
            # update s table
            down_score = s[i-1][j] + 0
            right_score = s[i][j-1] + 0
            diagonal_score = s[i-1][j-1] + (v[j-1] == w[i-1])
            best_move = max(right_score, down_score, diagonal_score)
            s[i][j] = best_move

            # update backtrack
            if s[i][j] == down_score:
                backtrack_result[i][j] = "down"
            elif s[i][j] == right_score:
                backtrack_result[i][j] = "right"
            elif s[i][j] == diagonal_score:
                backtrack_result[i][j] = "diagonal"
    return backtrack_result


def output_lcs(backtrack, v, i, j):
    if i == 0 or j == 0:
        return ""
    if backtrack[i][j] == "down":
        return output_lcs(backtrack, v, i-1, j)
    elif backtrack[i][j] == "right":
        return output_lcs(backtrack, v, i, j-1)
    else:
        return output_lcs(backtrack, v, i-1, j-1) + v[i-1]


if __name__ == "__main__":
    with open("../../Data/Lab8/LCS.txt", "r") as file:
        lines = file.readlines()
        v = lines[1].strip()
        w = lines[2].strip()
        res = lines[4].strip()
        # print(f"v is {v}, w is {w}")
        print(f"len of v is {len(v)}, len of w is {len(w)}")
        backtrack_result = lcs_backtrack(v, w)
        print(f"Backtrack result is {backtrack_result}")
        path = output_lcs(backtrack_result, v, len(w), len(v))
        print(f"Path is {path}")
