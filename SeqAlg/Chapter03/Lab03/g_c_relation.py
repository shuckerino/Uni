import parse_text_file
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

def draw_graph(y_values : list):
    x_values = [i for i in range(0, len(y_values))]
    plt.plot(x_values, y_values)
    plt.xlabel("X-axis data")
    plt.ylabel("Y-axis data")
    plt.title('multiple plots')
    plt.show()


if __name__ == "__main__":
    seq = parse_text_file.get_sequence_from_txt("data/oric_Vibrio_cholerae.txt")
    result_recursive = calculate_g_c_diff_recursive(seq, [0])
    result_recursive = result_recursive[1:] # remove dummy start value of 0
    # print(result_recursive)
    
    # result_iterative = calculate_g_c_diff_iterative(seq)
    # print(result_iterative)
    # print(f"Results are equal is {result_recursive == result_iterative}")
    
    draw_graph(result_recursive)