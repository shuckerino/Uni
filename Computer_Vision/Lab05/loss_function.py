#!/usr/bin/env python3

import sympy as sp

def calculate_influence_function(loss_function, para):
    
    # Calculate first derivative of the loss function
    derivative = sp.diff(loss_function, para)
    
    # Calculate second derivative of the loss function
    second_derivative = sp.diff(derivative, para)
    
    # Calculate influence function (first derivative / second derivative)
    influence_function = derivative / second_derivative
    
    return sp.simplify(influence_function)

def calculate_weight_function(loss_function, para):
    
    # Calculate first derivative of the loss function
    derivative = sp.diff(loss_function, para)

    # Calculate weight function (derivative / para)
    weight_function = derivative / para
    
    return sp.simplify(weight_function)
    