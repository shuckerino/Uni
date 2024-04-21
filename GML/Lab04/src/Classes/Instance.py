from typing import List, Any
import locale

class Instance:

    def __init__(self, values : List[Any], value_cols: List[int], clazz_col: int, clazz_one: Any):
        
        locale.setlocale(locale.LC_NUMERIC, 'de_DE.utf8')  # German locale for number format
        self.values = []
        for i in value_cols:
            o = values[i]
            try:
                # Try converting directly to float if possible
                self.values.append(float(o))
            except ValueError:
                # Try parsing as a locale-specific formatted number
                try:
                    self.values.append(locale.atof(o))
                except ValueError:
                    raise ValueError(f"Can't parse number from {o}")

        self.clazz_col = clazz_col
        self.clazz_one = clazz_one