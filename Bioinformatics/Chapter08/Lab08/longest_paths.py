

def ManhattanDP(n_rows: int, m_cols: int, down: list[list[int]], right: list[list[int]]) -> int:
    result_matrix = [[0 for _ in range(m_cols)] for _ in range(n_rows)]

    # go first column downwards
    for i in range(1, n_rows):
        result_matrix[i][0] = result_matrix[i-1][0] + down[i-1][0]
    # go first row rightwards
    for j in range(1, m_cols):
        result_matrix[0][j] = result_matrix[0][j-1] + right[0][j-1]

    # now go through the rest of the matrix and always choose the longest path
    for i in range(1, n_rows):
        for j in range(1, m_cols):
            path_from_top = result_matrix[i-1][j] + down[i-1][j]
            path_from_left = result_matrix[i][j-1] + right[i][j-1]
            result_matrix[i][j] = max(path_from_top, path_from_left)

    return result_matrix[n_rows-1][m_cols-1]  # return val of sink


if __name__ == "__main__":
    # parsing manhattan file
    with open("../../Data/Lab8/Manhattan.txt", "r") as file:
        all_lines = file.readlines()
        n, m = all_lines[1].split(" ")
        n = int(n)
        m = int(m)
        m_down = [line.strip() for line in all_lines[2:2+n]]
        m_right = [line.strip() for line in all_lines[2+n+1:2+2*n+2]]

        # convert from string matrices into int matrices
        m_down = [list(map(int, row.split())) for row in m_down]
        m_right = [list(map(int, row.split())) for row in m_right]
        # print(f"n is {n}")
        # print(f"m is {m}")
        print(f"down is {m_down}")
        print(f"right is {m_right}")
        res = ManhattanDP(n, m, m_down, m_right)
        print(f"The longest path is {res}")
