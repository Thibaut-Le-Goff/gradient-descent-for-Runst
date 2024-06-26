#include <stdio.h>
#include <stdbool.h>

// gcc gradient_descent.c && valgrind ./a.out

#define INPUTS_SIZE 3
#define TRY_NUMBER 1000
#define POWER_DIF 2.0

float OBSERVED_VALUES[3] = {1.4, 1.9, 3.2};
float INPUTS[3] = {0.5, 2.3, 2.9};

int main() {
    int try_number = TRY_NUMBER;
    bool slope_intercept_found[2] = {false, false};
    int true_counter = 0;
    float precision_success = 0.001;
    float slope_intercept_learning_rate[2] = {0.01, 0.1};
    int number_end = 0;

    float slope_intercept[2] = {0.0, 0.0};
    float step_size;
    float sum_derivative_square_residual;
    float predicted_height;
    float derivative_square_residual;

    for (int try = 0; try < try_number; try++) {

        // (0 = slope, 1 = intercept)
        for (int slope_or_intercept_indicator = 0; slope_or_intercept_indicator < 2; slope_or_intercept_indicator++) {
            if (true_counter == 2) {
                break;
            }

            printf("\nFor value (0 = slope, 1 = intercept): %d", slope_or_intercept_indicator);

            if (!slope_intercept_found[slope_or_intercept_indicator]) {
                sum_derivative_square_residual = 0.0;

                for (int j = 0; j < INPUTS_SIZE; j++) {
                    predicted_height = (slope_intercept[0] * INPUTS[j]) + slope_intercept[1];

                    if (slope_or_intercept_indicator == 0) {
                        derivative_square_residual = (-POWER_DIF * INPUTS[j]) * (OBSERVED_VALUES[j] - predicted_height);
                        sum_derivative_square_residual += derivative_square_residual;
                    }

                    if (slope_or_intercept_indicator == 1) {
                        derivative_square_residual = -POWER_DIF * (OBSERVED_VALUES[j] - predicted_height);
                        sum_derivative_square_residual += derivative_square_residual;
                    }
                }

                printf("\nSum of derivatives of square residuals: %f", sum_derivative_square_residual);

                step_size = sum_derivative_square_residual * slope_intercept_learning_rate[slope_or_intercept_indicator];
                printf("\nStep size: %f", step_size);

                printf("\nOld value: %f", slope_intercept[slope_or_intercept_indicator]);
                slope_intercept[slope_or_intercept_indicator] -= step_size;
                printf("\nNew value: %f", slope_intercept[slope_or_intercept_indicator]);

                if (sum_derivative_square_residual <= precision_success && sum_derivative_square_residual >= -precision_success) {
                    slope_intercept_found[slope_or_intercept_indicator] = true;
                    true_counter++;

                    if (slope_or_intercept_indicator == 0) {
                        printf("\n\nFound correct slope coefficient of prediction line!");
                        printf("\nSlope coefficient: %f", slope_intercept[slope_or_intercept_indicator]);
                    }

                    if (slope_or_intercept_indicator == 1) {
                        printf("\n\nFound correct intercept of prediction line!");
                        printf("\nIntercept: %f", slope_intercept[slope_or_intercept_indicator]);
                    }
                }
            }
        }

        if (true_counter == 2) {
            number_end = try;
            break;
        }
    }

    if (true_counter == 2) {
        printf("\nThe equation of the prediction line is: y = %f + %f", slope_intercept[0], slope_intercept[1]);
        printf("\nThe algorithm took %d tries to find the correct data.", number_end + 1);
    }
}
