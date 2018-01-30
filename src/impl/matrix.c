#include "matrix.h"
#include "stats.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef P_MATRIX_C
#define P_MATRIX_C

struct Matrix create_matrix(int h, int w, int populate) {
	int h_index;
	int w_index;
	struct Matrix matrix;

	matrix.values = malloc(h * sizeof(double **));

	for (h_index = 0; h_index < h; h_index++) {
		matrix.values[h_index] = malloc(w * sizeof(double *));
		if (populate)
			for (w_index = 0; w_index < w; w_index++)
				matrix.values[h_index][w_index] = malloc(sizeof(double));
	}
	matrix.h = h;
	matrix.w = w;
	matrix.is_populated = populate;

	return matrix;
}

double determinant(struct Matrix *matrix) {
	double det = 0.0;
	double term;
	int h_index = 0;
	int w_index = 0;
	int counter = 0;
	struct Permute permute = create_permutator(matrix->w);

	do {
		term = 1.0;
		w_index = 0;
		for (h_index = 0; h_index < matrix->h; h_index++) {
			term *= *matrix->values[permute.options[w_index]][h_index];
			w_index++;
		}
		term *= counter % 2 == 1 ? -1.0 : 1.0;
		det += term;
		counter++;
	} while (next_permutation(&permute));

	return det;
}

void delete_matrix(struct Matrix *matrix) {
	int h_index;
	int w_index;

	for (h_index = 0; h_index < matrix->h; h_index++) {
		if (matrix->is_populated)
			for (w_index = 0; w_index < matrix->w; w_index++)
				free(matrix->values[h_index][w_index]);
		free(matrix->values[h_index]);
	}
	free(matrix->values);

	return;
}

void print_matrix(struct Matrix *matrix) {
	int h_index;
	int w_index;

	for (h_index = 0; h_index < matrix->h; h_index++) {
		for (w_index = 0; w_index < matrix->w; w_index++) {
			printf("%f    ", *matrix->values[h_index][w_index]);
		}
		printf("\n");
	}
}

#endif

