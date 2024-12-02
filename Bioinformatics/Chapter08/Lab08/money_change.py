
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
YES, because in this example, every predecessor coin is max the half of the next coin. So to replace a coin, you must use
at least 2 smaller coins. So the biggest coin is always the right choice in order to use the minimum coin.

'''


'''
Task 1d: How to optimize memory mangement for big total values?

We only need to save |coins| values from before

'''


def get_min_num_of_coins_dynamic_prog(total: int, coins: list[int]) -> list[int]:

    subsolution_dict = dict()
    subsolution_dict[0] = 0
    # calculate every subsolution until total
    for m in range(1, total + 1):
        subsolution_dict[m] = 999999999
        # for current value, check which coins fit in
        for i in range(len(coins)):
            if coins[i] <= m:
                if subsolution_dict[m - coins[i]] + 1 < subsolution_dict[m]:
                    subsolution_dict[m] = subsolution_dict[m - coins[i]] + 1  # the current total - biggest coin that fit in + 1
    return subsolution_dict.get(total, -1)


def get_min_num_of_coins_dynamic_prog_optimized(total: int, coins: list[int]) -> list[int]:
    
    max_coin_value = max(coins)
    result_array = [None] * max_coin_value
    result_array[0] = 0
    current_value = 0  #counter to total
    
    while current_value <= total:
        for m in range(1, len(result_array)):
            result_array[m] = 999999999
            for i in range(len(coins)):
                if coins[i] <= m:
                    if result_array[m - coins[i]] + 1 < result_array[m]:
                        result_array[m] = result_array[m - coins[i]] + 1  # the current total - biggest coin that fit in + 1
        return result_array.get(total, -1)


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
