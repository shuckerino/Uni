
def get_sequence_from_txt(file_path : str) -> str:
    '''Reads genome sequence from text file\n
       Returns DNA sequence as string
    '''
    file = open(file_path, "r")
    content = file.readlines()
    sequence = "".join(content).replace('\r', '').replace('\n', '').upper()
    return sequence
 

def get_sequence_from_fasta(file_path : str) -> str:
    with open(file_path, "r") as fasta_file:
        file_without_header = fasta_file.read().splitlines()[1:]
        return "".join(file_without_header)