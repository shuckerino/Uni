import parse_input_files
import matplotlib.pyplot as plt

# recursive function
def calculate_g_c_diff_recursive(sequence : str, values: list) -> list:

    if sequence == "":
        return values
    
    if len(values) > 0:
        last_diff = values[-1]
    else:
        last_diff = 0
        
    current_diff = 0
    if sequence[0] == "C":
        current_diff -= 1
    elif sequence[0] == "G":
        current_diff += 1
    values.append(last_diff + current_diff) # write the updated value at the end of the list
    return calculate_g_c_diff_recursive(sequence[1:], values)

#iterative function
def calculate_g_c_diff_iterative(sequence : str) -> list:
    value_array = [0]
    for b in sequence:
        last_diff = value_array[-1]
        current_diff = 0
        if b == "C":
            current_diff -= 1
        elif b == "G":
            current_diff += 1
        value_array.append(last_diff + current_diff)
    return value_array[1:] #remove dummy start node 0

# def draw_graph(list_of_y_values : list[list]):
#     for i in range(len(list_of_y_values)):
#         plt.figure(i)
#         y_values = list_of_y_values[i]
#         x_values = [i for i in range(0, len(y_values))]
#         plt.plot(x_values, y_values)
#         plt.xlabel("X-axis data")
#         plt.ylabel("Y-axis data")
#         plt.title('multiple plots')

def draw_graph(list_of_y_values: list[list]):
    plt.figure()
    
    for i in range(len(list_of_y_values)):
        y_values = list_of_y_values[i]
        x_values = [j for j in range(len(y_values))]
        
        plt.plot(x_values, y_values, label=get_graph_label(i))  # Add a label for each plot

    # Add common labels and title
    plt.xlabel("Position in Sequence")
    plt.ylabel("G-C Difference")
    plt.title("G-C Difference for Multiple Sequences")
    plt.legend()  # Display the legend to identify each line
    plt.grid(True)  # Optional: add a grid for better readability
    
def calculate_vibrio_cholerae():
    seq = parse_input_files.get_sequence_from_fasta("data/genom_Vibrio_cholerae.fasta")
    return calculate_g_c_diff_iterative(seq)

def calculate_thermotoga_petrophila():
    seq = parse_input_files.get_sequence_from_fasta("data/genom_Thermotoga_petrophila.fasta")
    return calculate_g_c_diff_iterative(seq)
    
def calculate_escherichia_coli():
    seq = parse_input_files.get_sequence_from_fasta("data/genom_Escherichia_coli.fasta")
    return calculate_g_c_diff_iterative(seq)

def get_graph_label(i : int) -> str:
    if i == 0:
        return "Vibrio Cholerae"
    if i == 1:
        return "Thermotoga Petrohila"
    if i == 2:
        return "Escherichia Coli"

if __name__ == "__main__":
    list_of_results = []
    list_of_results.append(calculate_vibrio_cholerae())
    list_of_results.append(calculate_thermotoga_petrophila())
    list_of_results.append(calculate_escherichia_coli())
    draw_graph(list_of_results)
    plt.show()
    