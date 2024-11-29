
def get_min_num_of_coins_greedy(total: int, coins: list[int]) -> list[int]:
    used_coins = []

    if total == 0:
        used_coins

    while total > 0:
        for c in sorted(coins, reverse=True):
            if c <= total:
                used_coins.append(c)
                total -= c

    return used_coins


'''
Task 1b: Is the greedy algo optimal for some coin list?

Answer:
NO, every coin list has the same flaw, because the paradigm of greedy is just not optimal. Greedy just follows the most promising solution, and because of that we do not find
solutions that are "hidden"

'''


def get_min_num_of_coins_dynamic_prog(total: int, coins: list[int]) -> list[int]:

    subsolution_dict = dict()
    subsolution_dict[0] = 0
    # calculate every subsolution until total
    for m in range(1, total + 1):
        subsolution_dict[m] = 999999999
        # for current value, check which coins fit in
        for i in range(len(coins)):
            if m >= coins[i]:
                if subsolution_dict[m - coins[i]] + 1 < subsolution_dict[m]:
                    subsolution_dict[m] = subsolution_dict[m - coins[i]] + 1  # the current total - biggest coin that fit in + 1
    return subsolution_dict.get(total, -1)


if __name__ == "__main__":

    # Task 1a
    coins = [120, 40, 30, 24, 20, 10, 5, 4, 1]
    for total in range(23):
        used_coins = get_min_num_of_coins_greedy(total, coins)
        print(
            f"For total of {total} you need following {used_coins} coins. Count is {len(used_coins)}!")

    # Task 1c
    val = 40
    coins = [50, 25, 20, 10, 5, 1]
    res = get_min_num_of_coins_dynamic_prog(val, coins)
    print(f"Res with dynamic programming for {val} is {res}")
    val = 8074
    coins = [24, 13, 12, 7, 5, 3, 1]
    res = get_min_num_of_coins_dynamic_prog(val, coins)
    print(f"Res with dynamic programming for {val} is {res}")
