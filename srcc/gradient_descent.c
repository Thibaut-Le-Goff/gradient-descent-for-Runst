#include <stdio.h>
#include <stdlib.h>
#include "../include/network_parameters.h"
//#include <stdbool.h>

// gcc gradient_descent.c && valgrind ./a.out

#define INPUTS_SIZE 3
#define TRY_NUMBER 1000
#define POWER_DIF 2.0
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


//float OBSERVED_VALUES[3] = {1.4, 1.9, 3.2};
//float INPUTS[3] = {0.5, 2.3, 2.9};

float gradient_calculation(float* inputs, float *observed_values, Network_Parameters *slope_and_intercept, int slope_or_intercept_indicator);

void gradient_descent(float *inputs, float *observed_values) {
    
    //int try_number = TRY_NUMBER;
    //bool slope_intercept_found[2] = {false, false};
    /*
   
    float precision_success = 0.001;
    float SLOPE_INTERCEOT_LEARNING_RATE[2] = {0.01, 0.1};
    int number_end = 0;
    */

    int slope_intercept_found[2] = {0, 0};
    float slope = 0.0;
    float intercept = 0.0;

    Network_Parameters *slope_and_intercept = malloc(sizeof(Network_Parameters));
    slope_and_intercept->weights = &slope;
    slope_and_intercept->bias = &intercept;

    /*
    float SLOPE[NB_INPUTS * NB_DATAS_PER_INPUTS] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    float INTERCEPT[NB_DATAS_PER_INPUTS] = {0.0, 0.0, 0.0};
    */

    /*
    float step_size;
    float sum_derivative_square_residual;
    float predicted_height;
    float derivative_square_residual;
    */

    int number_end;

    for (int try = 0; try <= TRY_NUMBER - 1; try++) {

        // (0 = SLOPE, 1 = INTERCEPT)
        for (int slope_or_intercept_indicator = 0; slope_or_intercept_indicator <= 1; slope_or_intercept_indicator++) {
            if ((slope_intercept_found[0] + slope_intercept_found[1]) == 2) {
                break;
            }

            printf("\nFor value (0 = slope, 1 = intercept): %d", slope_or_intercept_indicator);

            if (!slope_intercept_found[slope_or_intercept_indicator]) {
                //sum_derivative_square_residual = 0.0;

                float sum_derivative_square_residual = gradient_calculation(inputs, observed_values, slope_and_intercept, slope_or_intercept_indicator);

                // matrix change start here
                /*
                
                for (int j = 0; j < INPUTS_SIZE; j++) {
                    //predicted_height = (SLOPE_INTERCEPT[0] * INPUTS[j]) + SLOPE_INTERCEPT[1];
                    predicted_height = (slope * inputs[j]) + intercept;

                    if (slope_or_intercept_indicator == 0) {
                        derivative_square_residual = (-POWER_DIF * inputs[j]) * (observed_values[j] - predicted_height);
                        sum_derivative_square_residual += derivative_square_residual;
                    }

                    if (slope_or_intercept_indicator == 1) {
                        derivative_square_residual = -POWER_DIF * (observed_values[j] - predicted_height);
                        sum_derivative_square_residual += derivative_square_residual;
                    }
                }

                if (slope_or_intercept_indicator == 0) {

                    printf("\nOld value: %f", *(slope_and_intercept->weights));
                    slope_and_intercept->weights -= step_size;
                    printf("\nNew value: %f", *(slope_and_intercept->weights));

                } 
                else if (slope_or_intercept_indicator == 1) {
                
                    printf("\nOld value: %f", *(slope_and_intercept->bias));
                    slope_and_intercept->bias -= step_size;
                    printf("\nNew value: %f", *(slope_and_intercept->bias));

                }
                */
                // matrix change end here

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


float gradient_calculation(float* inputs, float *observed_values, Network_Parameters *slope_and_intercept, int slope_or_intercept_indicator) {

    float predicted_height;
    float step_size;
    float derivative_square_residual;
    float sum_derivative_square_residual = 0.0;

    for (int j = 0; j < INPUTS_SIZE; j++) {
        //predicted_height = (SLOPE_INTERCEPT[0] * INPUTS[j]) + SLOPE_INTERCEPT[1];
        predicted_height = (*(slope_and_intercept->weights) * inputs[j]) + *(slope_and_intercept->bias);

        if (slope_or_intercept_indicator == 0) {
            derivative_square_residual = (-POWER_DIF * inputs[j]) * (observed_values[j] - predicted_height);
            sum_derivative_square_residual += derivative_square_residual;
        }

        if (slope_or_intercept_indicator == 1) {
            derivative_square_residual = -POWER_DIF * (observed_values[j] - predicted_height);
            sum_derivative_square_residual += derivative_square_residual;
        }
    }

    //printf("\nSum of derivatives of square residuals: %f", sum_derivative_square_residual);

    step_size = sum_derivative_square_residual * SLOPE_INTERCEOT_LEARNING_RATE[slope_or_intercept_indicator];
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