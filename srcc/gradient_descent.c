#include <stdio.h>
#include <stdlib.h>

#include "../include/network_parameters.h"

#include "../include/calculations/addition.h"
#include "../include/calculations/multiplication.h"
#include "../include/calculations/substraction.h"

// gcc gradient_descent.c && valgrind ./a.out

#define TRY_NUMBER 1000
#define POWER_DIF -2.0
#define PRECISION_SUCCESS 0.001

float SLOPE_INTERCEOT_LEARNING_RATE[2] = {0.01, 0.1};


/*
#define NB_INPUTS 3
#define NB_DATAS_PER_INPUTS 2 // = nb neurones at the first layer

float OBSERVED_VALUES[NB_INPUTS][NB_DATAS_PER_INPUTS] = {
    {1.4, 1.9},
    {1.4, 2},
    {1.4, 1.9}
};

float INPUTS[NB_INPUTS][NB_DATAS_PER_INPUTS] = {
    {0.5, 2.3},
    {0.5, 2},
    {0.5, 2.3}
};
*/


float gradient_calculation(int *net_struct, int *nb_propagations, float* inputs, float *observed_values, Network_Parameters *slope_and_intercept, int slope_or_intercept_indicator);

void gradient_descent(int *net_struct, int *nb_propagations, float *inputs, float *observed_values) {

    int slope_intercept_found[2] = {0, 0};
    /**/
    float slope = 0.0;

    float intercept = 0.0;

    Network_Parameters *slope_and_intercept = malloc(sizeof(Network_Parameters));
    slope_and_intercept->weights = &slope;
    slope_and_intercept->bias = &intercept;
    

    int number_end;

    for (int try = 0; try <= TRY_NUMBER - 1; try++) {

        // (0 = SLOPE, 1 = INTERCEPT)
        for (int slope_or_intercept_indicator = 0; slope_or_intercept_indicator <= 1; slope_or_intercept_indicator++) {
            if ((slope_intercept_found[0] + slope_intercept_found[1]) == 2) {
                break;
            }

            printf("\nFor value (0 = slope, 1 = intercept): %d", slope_or_intercept_indicator);

            if (!slope_intercept_found[slope_or_intercept_indicator]) {

                float sum_derivative_square_residual = gradient_calculation(net_struct, nb_propagations, inputs, observed_values, slope_and_intercept, slope_or_intercept_indicator);

                printf("\nSum of derivatives of square residuals: %f", sum_derivative_square_residual);

                if (sum_derivative_square_residual <= PRECISION_SUCCESS && sum_derivative_square_residual >= -PRECISION_SUCCESS) {
                // to adapt this to matrix we will propably do an average of every 
                // sum_derivative_square_residual of the element of the matrix
                //if (average_sum_derivative_square_residual <= precision_success && average_sum_derivative_square_residual >= -precision_success) {
                    slope_intercept_found[slope_or_intercept_indicator] = 1;
                    //true_counter++;

                    if (slope_or_intercept_indicator == 0) {
                        printf("\n\nFound correct slope coefficient of prediction line!");
                        printf("\nslope coefficient: %f", *(slope_and_intercept->weights));
                    }

                    if (slope_or_intercept_indicator == 1) {
                        printf("\n\nFound correct intercept of prediction line!");
                        printf("\nintercept: %f", *(slope_and_intercept->bias));
                    }
                }
            }
        }

        if ((slope_intercept_found[0] + slope_intercept_found[1]) == 2) {
            number_end = try;
            break;
        }
    }

    if ((slope_intercept_found[0] + slope_intercept_found[1]) == 2) {
        printf("\nThe equation of the prediction line is: y = %f + %f", *(slope_and_intercept->weights), *(slope_and_intercept->bias));
        printf("\nThe algorithm took %d tries to find the correct data.", number_end + 1);
    }

    free(slope_and_intercept);
}




float gradient_calculation(int *net_struct, int *nb_propagations, float* inputs, float *observed_values, Network_Parameters *slope_and_intercept, int slope_or_intercept_indicator) {
    int size_weights_array = net_struct[0] * net_struct[1];

    /*
    float predicted_value[net_struct[1]];
    float step_size[size_weights_array];
    float derivative_square_residual[size_weights_array];
    
    float *sum_derivative_square_residual[size_weights_array];

    for (int init_iterator = 0; init_iterator < size_weights_array; init_iterator++) {
        *(sum_derivative_square_residual[init_iterator]) = 0.0;
    }
    */

    int default_one_value = 1;
    
    /*
    float predicted_value;
    float step_size;
    float derivative_square_residual;
    float sum_derivative_square_residual = 0.0;
    */

    // (0 = SLOPE, 1 = INTERCEPT)
    if (slope_or_intercept_indicator == 0) {

        float *step_size[size_weights_array];
        float *sum_derivative_square_residual[size_weights_array];

        for (int init_iterator = 0; init_iterator < size_weights_array; init_iterator++) {
            *(sum_derivative_square_residual[init_iterator]) = 0.0;
        }

        for (int propagation_iterator = 0; propagation_iterator < *nb_propagations; propagation_iterator++) {
            /*
            predicted_value = (*(slope_and_intercept->weights) * inputs[propagation_iterator]) + *(slope_and_intercept->bias);

            derivative_square_residual = (-POWER_DIF * inputs[propagation_iterator]) * (observed_values[propagation_iterator] - predicted_value);

            sum_derivative_square_residual += derivative_square_residual;            
            */
            
            /// propagation
            float *pre_mul_predicted_value = mul(slope_and_intercept->weights, &inputs[propagation_iterator], &default_one_value, size_weights_array, net_struct[0]);
            float *predicted_value = add(pre_mul_predicted_value, slope_and_intercept->bias, net_struct[1]);
            ///
            
            float power_dif = POWER_DIF;
            float *pre_mul_derivative_square_residual = mul(&inputs[propagation_iterator], &power_dif, &default_one_value, net_struct[0], default_one_value);
            float *pre_sub_derivative_square_residual = sub(&observed_values[propagation_iterator], predicted_value, net_struct[1]);

            float *derivative_square_residual = mul(pre_mul_derivative_square_residual, pre_sub_derivative_square_residual, &default_one_value, net_struct[0], net_struct[1]);

            *sum_derivative_square_residual = add(derivative_square_residual, *sum_derivative_square_residual, size_weights_array);
        }

        *step_size = mul(*sum_derivative_square_residual, &SLOPE_INTERCEOT_LEARNING_RATE[slope_or_intercept_indicator], &default_one_value, net_struct[1], default_one_value);
    }

    // (0 = SLOPE, 1 = INTERCEPT)
    if (slope_or_intercept_indicator == 1) {

        float *step_size[net_struct[1]];
        float *sum_derivative_square_residual[net_struct[1]];

        for (int init_iterator = 0; init_iterator < size_weights_array; init_iterator++) {
            *(sum_derivative_square_residual[init_iterator]) = 0.0;
        }

        for (int propagation_iterator = 0; propagation_iterator < *nb_propagations; propagation_iterator++) {
            /*
            predicted_value = (*(slope_and_intercept->weights) * inputs[propagation_iterator]) + *(slope_and_intercept->bias);

            derivative_square_residual = -POWER_DIF * (observed_values[propagation_iterator] - predicted_value);

            sum_derivative_square_residual += derivative_square_residual;
            */

            /// propagation
            float *pre_mul_predicted_value = mul(slope_and_intercept->weights, &inputs[propagation_iterator], &default_one_value, size_weights_array, net_struct[0]);
            float *predicted_value = add(pre_mul_predicted_value, slope_and_intercept->bias, net_struct[1]);
            ///


            float power_dif = POWER_DIF;
            //float *pre_mul_derivative_square_residual = mul(&inputs[propagation_iterator], &power_dif, &default_one_value, net_struct[0], default_one_value);
            float *pre_sub_derivative_square_residual = sub(&observed_values[propagation_iterator], predicted_value, net_struct[1]);

            float *derivative_square_residual = mul(pre_sub_derivative_square_residual, &power_dif, &default_one_value, net_struct[1], default_one_value);

            *sum_derivative_square_residual = add(derivative_square_residual, *sum_derivative_square_residual, net_struct[1]);
        }

        *step_size = mul(*sum_derivative_square_residual, &SLOPE_INTERCEOT_LEARNING_RATE[slope_or_intercept_indicator], &default_one_value, net_struct[1], default_one_value);
    }


    //step_size = sum_derivative_square_residual * SLOPE_INTERCEOT_LEARNING_RATE[slope_or_intercept_indicator];

    printf("\nStep size: %f", step_size);

    if (slope_or_intercept_indicator == 0) {

        printf("\nOld value: %f", *(slope_and_intercept->weights));
        *(slope_and_intercept->weights) -= step_size;
        printf("\nNew value: %f", *(slope_and_intercept->weights));

    } 
    else if (slope_or_intercept_indicator == 1) {
                
        printf("\nOld value: %f", *(slope_and_intercept->bias));
        *(slope_and_intercept->bias) -= step_size;
        printf("\nNew value: %f", *(slope_and_intercept->bias));

    }
                
    return sum_derivative_square_residual;
}