def score_alignment(seq1, seq2):
    score = 0
    for s1, s2 in zip(seq1, seq2):
        if s1 == s2:
            score += 1  # Match
        elif s1 == '-' or s2 == '-':
            score -= 1  # Gap
        else:
            score -= 1  # Mismatch
    return score


def brute_force_alignment(seq1, seq2):
    best_score = -float('inf')
    best_alignment = ("", "")
    # Schleifen durch alle möglichen Positionen für die Ausrichtung
    for i in range(-len(seq2) + 1, len(seq1)):
        # Berechnung der Verschiebung
        seq1_shifted = seq1[max(0, i):]  # S1 angepasst
        seq2_shifted = seq2[max(0, -i):]  # S2 angepasst

        # Auffüllen mit Lücken, wenn nötig
        seq1_aligned = seq1_shifted.ljust(len(seq2_shifted), '-')
        seq2_aligned = seq2_shifted.ljust(len(seq1_shifted), '-')
        # Berechnen der Punktzahl für das Alignment
        score = score_alignment(seq1_aligned, seq2_aligned)
        # Aktualisieren des besten Alignments
        if score > best_score:
            best_score = score
            best_alignment = (seq1_aligned, seq2_aligned)
    return best_alignment


if __name__ == "__main__":
    seq1 = "ATGCATGC"
    seq2 = "TGCATGCA"
    best_alignment = brute_force_alignment(seq1, seq2)
    print("Bestes Alignment:")
    print(f"Sequenz 1: {best_alignment[0]}")
    print(f"Sequenz 2: {best_alignment[1]}")
