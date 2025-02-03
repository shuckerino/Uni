# Branch and Bound Sequence Alignment

This project implements a Branch and Bound algorithm for global sequence alignment.
The algorithm optimizes the traditional dynamic programming approach by pruning suboptimal paths early, improving performance, especially on large sequences.

## Algorithm Overview

The sequence alignment is based on minimizing the edit distance between two sequences, considering:

- Match: Cost = 0
- Mismatch: Cost = 1
- Gap (Insertion/Deletion): Cost = 1

The **Branch and Bound (BB)** technique introduces an upper threshold based on the Hamming distance and dynamically adjusts it during computation.
When the current cost exceeds this threshold, the algorithm prunes that path, avoiding unnecessary calculations.

## How to Run

1. **Prepare the Input**:
Place your input sequences in input.txt. Each case reads two consecutive lines as a sequence pair.

2. **Execute the Script**: 
Run the script using your python interpreter (recommended is a Python 3 version):
```py
python your_script.py
```
3. **View Results**:
After execution, alignment results and performance metrics are logged in the `logs/` directory:

- `logs/best_case_log.txt`
- `logs/worst_case_log.txt`
- `logs/average_case_log.txt`

Each log file contains:

- Input sequences
- Expected vs. actual costs
- Number of iterations, branches, and threshold changes
- Final aligned sequences
- Cost and traceback matrices

## Example Input (input.txt)

```
ACGTTGCAACGTTGCA
TGCAACGTACGTTGCA
```

## Example Output

####Case: logs/best_case_log####
s is ACGTTGCAACGTTGCA
t is TGCAACGTACGTTGCA
Alignment costs: 7
Best found alignments:
-ACGTTGCAACGTTGCA
TGCAACG-TACGTTGCA

For detailed metrics, check the corresponding log file in the `logs/` folder.

## Dependencies

- Python 3
- NumPy (`pip install numpy`)
- timeit (optional, can be used to measure actual runtime - install with `pip install timeit`)

## Notes

- Adjust `input.txt` and `case_dict` in the script to run different test cases
- Logs provide insights into algorithm efficiency with BB enabled


