import numpy as np

def branch_and_bound_alignment(s, t):
    n, m = len(s), len(t)
    max_cost = max(n, m)  # Triviale Schranke
    best_cost = [max_cost]  # Aktuelle beste Schranke (als Liste, um innerhalb von Funktionen änderbar zu sein)
    best_alignment = [("", "")]  # Hier speichern wir das beste Alignment

    # Kostenfunktion
    def cost(a, b):
        if a == b:
            return 0  # Match
        return 1  # Mismatch

    # Rekursive DP-Funktion mit Branch-and-Bound
    def dp(i, j, current_cost, alignment_s, alignment_t):
        # Basisfälle
        if i == n and j == m:
            # Wenn wir das Ende beider Sequenzen erreicht haben, überprüfen wir, ob dies das beste Alignment ist
            if current_cost < best_cost[0]:
                best_cost[0] = current_cost
                best_alignment[0] = (alignment_s, alignment_t)
            return current_cost
        if current_cost >= best_cost[0]:  # Abbrechen, wenn Kosten die Schranke überschreiten
            return float('inf')
        if i == n:
            return dp(i, j + 1, current_cost + 1, alignment_s + "-", alignment_t + t[j])
        if j == m:
            return dp(i + 1, j, current_cost + 1, alignment_s + s[i], alignment_t + "-")

        # Rekursion mit Branching
        match_cost = dp(i + 1, j + 1, current_cost + cost(s[i], t[j]), alignment_s + s[i], alignment_t + t[j])
        gap_s_cost = dp(i + 1, j, current_cost + 1, alignment_s + s[i], alignment_t + "-")
        gap_t_cost = dp(i, j + 1, current_cost + 1, alignment_s + "-", alignment_t + t[j])

        return min(match_cost, gap_s_cost, gap_t_cost)

    # Starte die Berechnung
    alignment_cost = dp(0, 0, 0, "", "")
    return alignment_cost, best_alignment[0]

# Beispielaufruf
s = "ATGTTATA"
t = "ATCGTCC"
alignment_cost, best_alignment = branch_and_bound_alignment(s, t)
print(f"Alignment-Kosten: {alignment_cost}")
print(f"Bestes Alignment:\n{best_alignment[0]}\n{best_alignment[1]}")
