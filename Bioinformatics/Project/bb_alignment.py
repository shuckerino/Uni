import numpy as np

best_alignments = [("", "")]  # Hier speichern wir das beste Alignment
recursion_count = 0
res_table = {}

def read_sequences(file_path):
    """Reads sequences from a file."""
    with open(file_path, 'r') as file:
        sequences = file.readlines()
    #return "ATGTTATA", "ATCGTCC"
    return sequences[0].strip(), sequences[1].strip()

 # Kostenfunktion
def cost(a, b):
    if a == b:
        return 0  # Match
    return 1  # Mismatch


def branch_and_bound_alignment(s, t):
    global best_alignments
    n, m = len(s), len(t)
    max_cost = max(n, m) - 10  # Triviale Schranke
    best_cost = [max_cost]  # Aktuelle beste Schranke (als Liste, um innerhalb von Funktionen änderbar zu sein)
    
    # Rekursive DP-Funktion mit Branch-and-Bound
    def dp(i, j, current_cost, alignment_s, alignment_t):
        global best_alignments
        global recursion_count
        recursion_count += 1
                
        # Basisfälle
        if i == n and j == m:
            
            # We found a better solution
            if current_cost < best_cost[0]:
                best_cost[0] = current_cost
                best_alignments = [(alignment_s, alignment_t)]
                #if recursion_count % 1000 == 0:
                print(f"New best alignment found with cost {current_cost}:\n{alignment_s}\n{alignment_t}\n")
            elif current_cost == best_cost[0]:
                best_alignments.append((alignment_s, alignment_t))
            return current_cost
        
        remaining_cost = sum(1 for x, y in zip(s[i:], t[j:]) if x != y) + abs(len(s[i:]) - len(t[j:]))
        # If the current cost is already larger than a found solution, bound
        if remaining_cost >= best_cost[0]:
            #if recursion_count % 1000 == 0:
            print(f"Pruning branch at i={i}, j={j}, current_cost={current_cost}\n")
            return float('inf')
        
        if i == n:
            return dp(i, j + 1, current_cost + 1, alignment_s + "-", alignment_t + t[j])
        if j == m:
            return dp(i + 1, j, current_cost + 1, alignment_s + s[i], alignment_t + "-")

        # Rekursion mit Branching
        match_cost = dp(i + 1, j + 1, current_cost + cost(s[i], t[j]), alignment_s + s[i], alignment_t + t[j])
        gap_s_cost = dp(i + 1, j, current_cost + 1, alignment_s + s[i], alignment_t + "-")
        gap_t_cost = dp(i, j + 1, current_cost + 1, alignment_s + "-", alignment_t + t[j])

        min_cost = min(match_cost, gap_s_cost, gap_t_cost)
        res_table[(i, j)] = min_cost
        return min_cost
    
    # Starte die Berechnung
    alignment_cost = dp(0, 0, 0, "", "")
    return alignment_cost, best_alignments

if __name__ == "__main__":
    #s = "ATGTTATA"
    #t = "ATCGTCC"
    sequences_file = "./input.txt"
    s, t = read_sequences(sequences_file)
    print(f"s is {s}")
    print(f"t is {t}")
    
    alignment_cost, best_alignments = branch_and_bound_alignment(s, t)
    print(f"Alignment costs: {alignment_cost}")
    print(f"Best found alignments:\n")
    for alignment_pair in best_alignments:
        print(f"{alignment_pair[0]}, {alignment_pair[1]}")
