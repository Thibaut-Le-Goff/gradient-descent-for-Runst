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


float *gradient_calculation(int *net_struct, int *nb_propagations, float *inputs, float *observed_values, Network_Parameters *slope_and_intercept, int slope_or_intercept_indicator);

void gradient_descent(int *net_struct, int *nb_propagations, float *inputs, float *observed_values) {

    int slope_intercept_found[2] = {0, 0};

    int size_weights_array = net_struct[0] * net_struct[1];

    Network_Parameters *slope_and_intercept = malloc(sizeof(Network_Parameters));

    slope_and_intercept->weights = malloc(net_struct[0] * net_struct[1] * sizeof(float));
    for(int vector_iterator = 0; vector_iterator < size_weights_array; vector_iterator++) {
        slope_and_intercept->weights[vector_iterator] = 0;
    }
    
    slope_and_intercept->bias = malloc(net_struct[1] * sizeof(float));
    for(int vector_iterator = 0; vector_iterator < size_weights_array; vector_iterator++) {
        slope_and_intercept->bias[vector_iterator] = 0;
    }

    int number_end;

    for (int try = 0; try < TRY_NUMBER; try++) {

        // (0 = SLOPE, 1 = INTERCEPT)
        for (int slope_or_intercept_indicator = 0; slope_or_intercept_indicator <= 1; slope_or_intercept_indicator++) {
            if ((slope_intercept_found[0] + slope_intercept_found[1]) == 2) {
                break;
            }

            printf("\nFor value (0 = slope, 1 = intercept): %d", slope_or_intercept_indicator);

            if (!slope_intercept_found[slope_or_intercept_indicator]) {

                float *sum_derivative_square_residual = gradient_calculation(net_struct, nb_propagations, inputs, observed_values, slope_and_intercept, slope_or_intercept_indicator);

                printf("\nSum of derivatives of square residuals:");
                for(int vector_iterator = 0; vector_iterator < size_weights_array; vector_iterator++) {
                    printf(" %f,", sum_derivative_square_residual[vector_iterator]);
                }
                printf("\n\n");

                if (*sum_derivative_square_residual <= PRECISION_SUCCESS && *sum_derivative_square_residual >= -PRECISION_SUCCESS) {
                // to adapt this to matrix we will propably do an average of every 
                // sum_derivative_square_residual of the element of the matrix
                //if (average_sum_derivative_square_residual <= precision_success && average_sum_derivative_square_residual >= -precision_success) {
                    slope_intercept_found[slope_or_intercept_indicator] = 1;
                    //true_counter++;

                    if (slope_or_intercept_indicator == 0) {
                        printf("\n\nFound correct slope coefficient of prediction line!");
                        printf("\nslope coefficient:");
                        for(int vector_iterator = 0; vector_iterator <= size_weights_array; vector_iterator++) {
                            printf(" %f,", slope_and_intercept->weights[vector_iterator]);
                        }
                        printf("\n\n");
                    }

                    if (slope_or_intercept_indicator == 1) {
                        printf("\n\nFound correct intercept of prediction line!");
                        printf("\nintercept:");
                        for(int vector_iterator = 0; vector_iterator <= net_struct[0]; vector_iterator++) {
                            printf(" %f,", slope_and_intercept->bias[vector_iterator]);
                        }
                        printf("\n\n");
                    }
                }

                free(sum_derivative_square_residual);
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

    free(slope_and_intercept->weights);
    free(slope_and_intercept->bias);
    free(slope_and_intercept);
}





float *gradient_calculation(int *net_struct, int *nb_propagations, float *inputs, float *observed_values, Network_Parameters *slope_and_intercept, int slope_or_intercept_indicator) {
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

        //float *step_size[size_weights_array];
        //float sum_derivative_square_residual[size_weights_array];
        float *sum_derivative_square_residual = (float *)malloc(size_weights_array * sizeof(float));

        for (int init_iterator = 0; init_iterator < size_weights_array; init_iterator++) {
            sum_derivative_square_residual[init_iterator] = 0.0;
        }

        for (int propagation_iterator = 0; propagation_iterator < *nb_propagations; propagation_iterator++) {
            /*
            predicted_value = (*(slope_and_intercept->weights) * inputs[propagation_iterator]) + *(slope_and_intercept->bias);

            derivative_square_residual = (-POWER_DIF * inputs[propagation_iterator]) * (observed_values[propagation_iterator] - predicted_value);

            sum_derivative_square_residual += derivative_square_residual;            
            */
            
            /// propagation
            float *pre_mul_predicted_value = mul(slope_and_intercept->weights, &inputs[propagation_iterator], &default_one_value, size_weights_array, net_struct[0]);
            printf("pre_mul_predicted_value = slope_and_intercept->weights * &inputs[propagation_iterator]:\n");
            //for(int vector_iterator = 0; vector_iterator < net_struct[1]; vector_iterator++) {
            //    printf("%f = %f * %f\n", pre_mul_predicted_value[vector_iterator], slope_and_intercept->weights[vector_iterator], inputs[propagation_iterator][vector_iterator]);
            //}

            //printf("predicted_value:\n");
            float *predicted_value = add(pre_mul_predicted_value, slope_and_intercept->bias, net_struct[1]);
            free(pre_mul_predicted_value);
            ///
            
            float power_dif = POWER_DIF;
            float *pre_mul_derivative_square_residual = mul(&inputs[propagation_iterator], &power_dif, &default_one_value, net_struct[0], default_one_value);
            //printf("pre_sub_derivative_square_residual = &inputs[propagation_iterator] * &power_dif:\n");
            /*
            for(int vector_iterator = 0; vector_iterator < net_struct[1]; vector_iterator++) {
                printf("%f = %f * %f\n", pre_sub_derivative_square_residual[vector_iterator], inputs[propagation_iterator][vector_iterator], power_dif);
            }
            */

            float *pre_sub_derivative_square_residual = sub(&observed_values[propagation_iterator], predicted_value, net_struct[1]);
            free(predicted_value);

            float *derivative_square_residual = mul(pre_mul_derivative_square_residual, pre_sub_derivative_square_residual, &default_one_value, net_struct[0], net_struct[1]);
            //float *sum_derivative_square_residual = add(derivative_square_residual, sum_derivative_square_residual, size_weights_array);
            //*sum_derivative_square_residual = add(derivative_square_residual, sum_derivative_square_residual, size_weights_array);
            //printf("pre_sub_derivative_square_residual = &inputs[propagation_iterator] * &power_dif:\n");
            
            /*
            for(int vector_iterator = 0; vector_iterator < net_struct[1]; vector_iterator++) {
                printf("%f = %f * %f\n", pre_sub_derivative_square_residual[vector_iterator], inputs[propagation_iterator][vector_iterator], power_dif);
            }
            */

            free(pre_mul_derivative_square_residual);
            free(pre_sub_derivative_square_residual);

            for(int vector_iterator = 0; vector_iterator < size_weights_array; vector_iterator++) {
                sum_derivative_square_residual[vector_iterator] = sum_derivative_square_residual[vector_iterator] + derivative_square_residual[vector_iterator];
            }
            free(derivative_square_residual);
        }

        //float *step_size[size_weights_array] = mul(*sum_derivative_square_residual, &SLOPE_INTERCEOT_LEARNING_RATE[slope_or_intercept_indicator], &default_one_value, net_struct[1], default_one_value);
        float *step_size = mul(sum_derivative_square_residual, &SLOPE_INTERCEOT_LEARNING_RATE[slope_or_intercept_indicator], &default_one_value, net_struct[1], default_one_value);
        
        printf("\nStep size:");
        for(int vector_iterator = 0; vector_iterator < size_weights_array; vector_iterator++) {
            printf(" %f,", step_size[vector_iterator]);
        }
        printf("\n");

        printf("\nOld value:");
        for(int vector_iterator = 0; vector_iterator < size_weights_array; vector_iterator++) {
            printf(" %f,", slope_and_intercept->weights[vector_iterator]);
        }

        //slope_and_intercept->weights = sub(slope_and_intercept->weights, step_size, size_weights_array);
        for(int vector_iterator = 0; vector_iterator < size_weights_array; vector_iterator++) {
            slope_and_intercept->weights[vector_iterator] = slope_and_intercept->weights[vector_iterator] - step_size[vector_iterator];
        }

        printf("\nNew value:");
        for(int vector_iterator = 0; vector_iterator < size_weights_array; vector_iterator++) {
            printf(" %f,", slope_and_intercept->weights[vector_iterator]);
        }
        printf("\n\n");

        free(step_size);
        return (float *)sum_derivative_square_residual;
    }

    // (0 = SLOPE, 1 = INTERCEPT)
    if (slope_or_intercept_indicator == 1) {

        //float *step_size[net_struct[1]];
        float *sum_derivative_square_residual = (float *)malloc(net_struct[1] * sizeof(float));

        //float *sum_derivative_square_residual[net_struct[1]];

        for (int init_iterator = 0; init_iterator < size_weights_array; init_iterator++) {
            sum_derivative_square_residual[init_iterator] = 0.0;
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
            free(pre_mul_predicted_value);
            ///


            float power_dif = POWER_DIF;
            //float *pre_mul_derivative_square_residual = mul(&inputs[propagation_iterator], &power_dif, &default_one_value, net_struct[0], default_one_value);
            float *pre_sub_derivative_square_residual = sub(&observed_values[propagation_iterator], predicted_value, net_struct[1]);
            //printf("pre_sub_derivative_square_residual = &inputs[propagation_iterator] * &power_dif:\n");
            /*
            for(int vector_iterator = 0; vector_iterator < net_struct[1]; vector_iterator++) {
                printf("%f = %f * %f\n", pre_sub_derivative_square_residual[vector_iterator], inputs[propagation_iterator][vector_iterator], power_dif);
            }
            */
            
            free(predicted_value);

            float *derivative_square_residual = mul(pre_sub_derivative_square_residual, &power_dif, &default_one_value, net_struct[1], default_one_value);
            free(pre_sub_derivative_square_residual);

            //*sum_derivative_square_residual = add(derivative_square_residual, sum_derivative_square_residual, net_struct[1]);
            
            for(int vector_iterator = 0; vector_iterator < size_weights_array; vector_iterator++) {
                sum_derivative_square_residual[vector_iterator] = sum_derivative_square_residual[vector_iterator] + derivative_square_residual[vector_iterator];
            }
            free(derivative_square_residual);
        }

        float *step_size = mul(sum_derivative_square_residual, &SLOPE_INTERCEOT_LEARNING_RATE[slope_or_intercept_indicator], &default_one_value, net_struct[1], default_one_value);
        
        printf("\nStep size:");
        for(int vector_iterator = 0; vector_iterator < net_struct[1]; vector_iterator++) {
            printf(" %f,", step_size[vector_iterator]);
        }
        printf("\n");

        printf("\nOld value:");
        for(int vector_iterator = 0; vector_iterator < net_struct[1]; vector_iterator++) {
            printf(" %f,", slope_and_intercept->bias[vector_iterator]);
        }                
        //slope_and_intercept->bias = sub(slope_and_intercept->bias, step_size, net_struct[1]);
        for(int vector_iterator = 0; vector_iterator < net_struct[1]; vector_iterator++) {
            slope_and_intercept->bias[vector_iterator] = slope_and_intercept->bias[vector_iterator] - step_size[vector_iterator];
        }

        printf("\nNew value:");
        for(int vector_iterator = 0; vector_iterator < net_struct[1]; vector_iterator++) {
            printf(" %f,", slope_and_intercept->bias[vector_iterator]);
        }
        printf("\n\n");

        free(step_size);
        return (float *)sum_derivative_square_residual;
    }


    //step_size = sum_derivative_square_residual * SLOPE_INTERCEOT_LEARNING_RATE[slope_or_intercept_indicator];

    /*
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
    */

    return NULL;
}