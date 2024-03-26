#include <stdio.h>
#include <stdlib.h>

#include "../include/gradient_descent.h"

#include "../include/calculations/addition.h"
#include "../include/calculations/multiplication.h"
#include "../include/calculations/substraction.h"

#define NB_PROPAGATIONS 3
//#define NB_NEURONES_FIRST_LAYER 2
//#define NB_NEURONES_LAST_LAYER 3

int main() {
    float observed_values[NB_PROPAGATIONS] = {1.4, 1.9, 3.2};
    float inputs[NB_PROPAGATIONS] = {0.5, 2.3, 2.9};

    /*
    float INPUTS[NB_PROPAGATION][NB_NEURONES_FIRST_LAYER] = {
        {0.5, 2.3},
        {0.5, 2},
        {0.5, 2.3}
    };

    float OBSERVED_VALUES[NB_PROPAGATION][NB_NEURONES_LAST_LAYER] = {
        {1.4, 1.9, 2.4},
        {1.4, 2, 1.5},
        {1.4, 1.9, 1.2}
    };
    */

    int nb_propagations = NB_PROPAGATIONS;

    gradient_descent(&nb_propagations, inputs, observed_values);


    printf("\nlayer 1 :\n");
    int weights_1[] = {0, 1, 2, 3, 4, 5};
    int inputs_2[] = {0, 1, 2};

    int column_result = 1; // 1 because we want a vector

    size_t size1 = sizeof(weights_1) / sizeof(weights_1[0]);
    size_t size2 = sizeof(inputs) / sizeof(inputs[0]);
    int *neurones_1 = mul(weights_1, inputs_2, &column_result, size1, size2);
    //int *neurones_1 = mul(weights_1, inputs, &column_result);

    int iteratore_layer_1 = size1 / size2;
    printf("\nNumber at the neurones of the layer 1 : ");
    for (int i = 0; i < iteratore_layer_1; i++) {
        printf("%d ", neurones_1[i]);
    }
    printf("\n");

    printf("\nlayer 2 :\n");
    int weights_2[] = {0, 1, 2, 3, 4, 5};
    size_t size3 = sizeof(weights_2) / sizeof(weights_2[0]);
    size_t size4 = (size1 / size2);
    int *neurones_2 = mul(weights_2, neurones_1, &column_result, size3, size4);
    //int *neurones_2 = mul(weights_2, neurones_1, &column_result);

    int iteratore_layer_2 = size3 / size4;
    printf("\nNumber at the neurones of the layer 2 : ");
    for (int i = 0; i < iteratore_layer_2; i++) {
        printf("%d ", neurones_2[i]);
    }
    printf("\n");


    printf("\ntest :\n");
    int mat[] = {0, 1, 2, 3, 4, 5};
    //int scal[] = {2};
    int scal = 2;
    size_t size_mat = sizeof(mat) / sizeof(mat[0]);
    //size_t size_scal = sizeof(scal) / sizeof(scal[0]);
    size_t size_scal = 1;
    int *res_test = mul(mat, &scal, &column_result, size_mat, size_scal);
    //int *neurones_2 = mul(weights_2, neurones_1, &column_result);

    int iteratore_test = size_mat / size_scal;
    printf("\ntest to see if I can multiply a vector by a number : ");
    for (int i = 0; i < iteratore_test; i++) {
        printf("%d ", res_test[i]);
    }
    printf("\n");

    free(neurones_1);
    free(neurones_2);
    free(res_test);
}