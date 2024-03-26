#include <stdio.h>
#include <stdlib.h>

int* mul(const int *mat1, const int *mat2, const int *column_result, const size_t size1, const size_t size2) {

    int number_row_mat2 = size2 / (*column_result);
    //fprintf(stderr, "\nnumber_row_mat2 = size2 / (*column_result) : %d = %zu / %d\n", number_row_mat2, size2, (*column_result));

    int number_row_mat1 = size1 / number_row_mat2;
    //fprintf(stderr, "number_row_mat1 = size1 / number_row_mat2 : %d = %zu / %d\n", number_row_mat1, size1, number_row_mat2);

    // the number of rows of mat1 is equal to the number of 
    // rows of the matrix as the result
    int *mat_result = (int*)malloc(((*column_result) * number_row_mat1) * sizeof(int));
    //printf("\nle resultat doit contenir %d nombres", sizeof(*mat_result));

    for (int row_mat1 = 0; row_mat1 < number_row_mat1; row_mat1++) {

        // The number of columns of the second matrix (mat2) is  
        // equal to the number of columns of the matrix as the result :
        for (int col_mat2 = 0; col_mat2 < *column_result; col_mat2++) {

            int result = 0;

            for (int row_mat2 = 0; row_mat2 < number_row_mat2; row_mat2++) {

                // The number columns of mat1 is equal
                // to the number of rows of mat2 :
                int index_mat1 = (number_row_mat2 * row_mat1) + row_mat2;

                // The number of columns of the second matrix (mat2) is equal 
                // to the number of columns of the matrix as the result :                
                int index_mat2 = (*column_result * row_mat2) + col_mat2;

                int pre_result = mat1[index_mat1] * mat2[index_mat2];
                result += pre_result;
            }
            
            // The number of columns of the second matrix (mat2) is equal 
            // to the number of columns of the matrix as the result : 

            // the number of rows of mat1 is equal to the number of 
            // rows of the matrix as the result
            mat_result[(*column_result * row_mat1) + col_mat2] = result;
        }
    }

    return mat_result;
}

