def MotivSucheGreedy(Dna, k):
    t = len(Dna)
    best_motives = []
    besteDistanz = 99999999
    for i in range(len(Dna)):
        best_motives.append(Dna[i][:k])

    for j in range(len(Dna[0]) - k + 1):
        motiv1 = Dna[0][j:j+k]
        motives = [motiv1]
        for i in range(1, t):  # iterate from 2 to t
            profile = get_profile_matrix()  # profile matrix should have list of cols
            best_fit = get_most_fitting_kmer_of_sequence(Dna[i], profile)
            motives.append(best_fit)
        d = Score(motives)
        if d < besteDistanz:
            besteDistanz = d
            best_motives = motives


def get_prob_for_kmer(kmer, profile_matrix):
    # iterate over length of kmer
    # take character and take prob of profile_matrix
    # return the product of the probs
    pass


def get_most_fitting_kmer_of_sequence(seq, profil):
    pass


def get_profile_matrix():
    pass  # siehe Lab5
