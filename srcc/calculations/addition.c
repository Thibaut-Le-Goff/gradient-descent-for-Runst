#include <stdio.h>
#include <stdlib.h>

int* add(const int *mat1, const int *mat2, const int size) {

    int *vec_result = (int*)malloc(size * sizeof(int));

    for(int vector_iterator = 0; vector_iterator < size; vector_iterator++) {

        vec_result[vector_iterator] = mat1[vector_iterator] + mat2[vector_iterator];
    }

    return vec_result;
}
