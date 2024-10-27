
def get_sequence_from_txt(file_path : str) -> str:
    '''Reads genome sequence from text file\n
       Returns DNA sequence as string
    '''
    file = open(file_path, "r")
    content = file.readlines()
    sequence = "".join(content).replace('\r', '').replace('\n', '').upper()
    return sequence