#include <stdio.h>
#include <stdlib.h>

float *add(const float *mat1, const float *mat2, const int size) {

    float *vec_result = (float*)malloc(size * sizeof(float));

    for(int vector_iterator = 0; vector_iterator < size; vector_iterator++) {

        vec_result[vector_iterator] = mat1[vector_iterator] + mat2[vector_iterator];
    }

    return vec_result;
}
