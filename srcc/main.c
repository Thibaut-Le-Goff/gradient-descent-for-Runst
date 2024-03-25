#include <stdio.h>
#include "../include/gradient_descent.h"

int main() {
    float observed_values[3] = {1.4, 1.9, 3.2};
    float inputs[3] = {0.5, 2.3, 2.9};

    gradient_descent(inputs, observed_values);
}