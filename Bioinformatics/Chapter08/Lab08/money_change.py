
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


if __name__ == "__main__":
    coins = [120, 40, 30, 24, 20, 10, 5, 4, 1]
    for total in range(22):
        used_coins = get_min_num_of_coins_greedy(total, coins)
        print(
            f"For total of {total} you need following {used_coins} coins. Count is {len(used_coins)}!")
