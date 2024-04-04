#include <stdio.h>
#include <stdlib.h>

#include "../include/gradient_descent.h"

#include "../include/calculations/addition.h"
#include "../include/calculations/multiplication.h"
#include "../include/calculations/substraction.h"

#define NB_PROPAGATIONS 3
#define NB_NEURONES_FIRST_LAYER 1
#define NB_NEURONES_LAST_LAYER 1

int main() {
    int net_struct[2] = {NB_NEURONES_FIRST_LAYER, NB_NEURONES_LAST_LAYER};

    /*
    float slope = 0.0;
    float intercept = 0.0;

    Network_Parameters *slope_and_intercept = malloc(sizeof(Network_Parameters));
    slope_and_intercept->weights = &slope;
    slope_and_intercept->bias = &intercept;
    

    float observed_values[NB_PROPAGATIONS] = {1.4, 1.9, 3.2};
    float inputs[NB_PROPAGATIONS] = {0.5, 2.3, 2.9};
    */

    /**/
    float inputs[NB_PROPAGATIONS][NB_NEURONES_FIRST_LAYER] = {
        {0.5},
        {2.3},
        {2.9}
    };

    float observed_values[NB_PROPAGATIONS][NB_NEURONES_LAST_LAYER] = {
        {1.4},
        {1.9},
        {3.2}
    };
    

    int nb_propagations = NB_PROPAGATIONS;

    gradient_descent(net_struct, &nb_propagations, (float *)inputs, (float *)observed_values);



    printf("\nlayer 1 :\n");
    float weights_1[] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};
    float inputs_2[] = {0.0, 1.0, 2.0};

    int column_result = 1; // 1 because we want a vector

    int size_weights_1 = sizeof(weights_1) / sizeof(weights_1[0]);
    int size_inputs = sizeof(inputs) / sizeof(inputs[0]);
    float *neurones_1 = mul(weights_1, inputs_2, &column_result, size_weights_1, size_inputs);
    //int *neurones_1 = mul(weights_1, inputs, &column_result);

    int iteratore_layer_1 = size_weights_1 / size_inputs;
    printf("\nNumber at the neurones of the layer 1 : ");
    
    printf("\n");
    for (int i = 0; i < iteratore_layer_1; i++) {
        printf("%f ", neurones_1[i]);
    }
    printf("\n");


    printf("\nlayer 2 :\n");
    float weights_2[] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};
    int size_weights_2 = sizeof(weights_2) / sizeof(weights_2[0]);
    int size_inputs_2 = (size_weights_1 / size_inputs);
    float *neurones_2 = mul(weights_2, neurones_1, &column_result, size_weights_2, size_inputs_2);
    //int *neurones_2 = mul(weights_2, neurones_1, &column_result);

    int iteratore_layer_2 = size_weights_2 / size_inputs_2;
    printf("\nNumber at the neurones of the layer 2 : ");
    
    printf("\n");
    for (int i = 0; i < iteratore_layer_2; i++) {
        printf("%f ", neurones_2[i]);
    }
    printf("\n");


    printf("\ntest :\n");
    float mat[] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};
    //int scal[] = {2};
    float scal = 2.0;
    int size_mat = sizeof(mat) / sizeof(mat[0]);
    //int size_scal = sizeof(scal) / sizeof(scal[0]);
    int size_scal = 1;
    float *res_test = mul(mat, &scal, &column_result, size_mat, size_scal);
    //int *neurones_2 = mul(weights_2, neurones_1, &column_result);

    int iteratore_test = size_mat / size_scal;
    printf("\ntest to see if I can multiply a vector by a number : ");

    printf("\n");
    for (int i = 0; i < iteratore_test; i++) {
        printf("%f ", res_test[i]);
    }
    printf("\n");

    free(neurones_1);
    free(neurones_2);
    free(res_test);
}