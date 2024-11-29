
def get_element_index_in_list(element_list, val) -> int:
    left = 0
    right = len(element_list) - 1

    while left <= right:
        mid = (right + left) // 2
        if val < element_list[mid]:
            right = mid - 1
        elif val > element_list[mid]:
            left = mid + 1
        else:
            return mid  # mid is index of val
    return -1
