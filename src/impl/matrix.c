#include "matrix.h"
#include "stats.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef P_MATRIX_C
#define P_MATRIX_C

#define ZERO 0.0000000001

struct Matrix create_matrix(int h, int w) {
	int h_index;
	int w_index;
	struct Matrix matrix;

	matrix.values = malloc(h * sizeof(double *));

	for (h_index = 0; h_index < h; h_index++) {
		matrix.values[h_index] = malloc(w * sizeof(double));
	}
	matrix.h = h;
	matrix.w = w;

	return matrix;
}

struct Matrix create_matrix_zeroes(int h, int w) {
	int h_index;
	int w_index;
	struct Matrix matrix = create_matrix(h, w);

	for (h_index = 0; h_index < h; h_index++) {
		for (w_index = 0; w_index < w; w_index++) {
			matrix.values[h_index][w_index] = 0.0;
		}
	}

	return matrix;
}

struct Matrix multiply_matrix(struct Matrix *left, struct Matrix *right) {
	int h_index;
	int w_index;
	int w_out;
	double sum;
	struct Matrix output = create_matrix(left->h, right->w);

	for (h_index = 0; h_index < left->h; h_index++) {
		for (w_out = 0; w_out < right->w; w_out++) {
			sum = 0;
			for (w_index = 0; w_index < left->w; w_index++) {
				sum += left->values[h_index][w_index] * right->values[w_index][w_out];
			}
			output.values[h_index][w_out] = sum;
		}
	}

	return output;
}

struct Matrix add_matrix(struct Matrix *left, struct Matrix *right, int put_left) {
	int h_index;
	int w_index;
	struct Matrix output;

	if (put_left) output = *left;
	else output = create_matrix(left->h, left->w);

	for (h_index = 0; h_index < left->h; h_index++)
		for (w_index = 0; w_index < left->w; w_index++)
			output.values[h_index][w_index] = left->values[h_index][w_index] + right->values[h_index][w_index];

	return output;
}

struct Matrix subtract_matrix(struct Matrix *left, struct Matrix *right, int put_left) {
	int h_index;
	int w_index;
	struct Matrix output;

	if (put_left) output = *left;
	else output = create_matrix(left->h, left->w);

	for (h_index = 0; h_index < left->h; h_index++)
		for (w_index = 0; w_index < left->w; w_index++)
			output.values[h_index][w_index] = left->values[h_index][w_index] - right->values[h_index][w_index];

	return output;
}

struct Matrix *column_element_product(struct Matrix *left, struct Matrix *right) {
	int index;
	int h_index;
	int w_index;
	struct Matrix *out;

	if (left->h != right->h) return 0;

	out = malloc(sizeof(struct Matrix) * left->w);
	for (index = 0; index < left->w; index++) {
		out[index] = create_matrix(right->h, right->w);
		for (h_index = 0; h_index < right->h; h_index++) {
			for (w_index = 0; w_index < right->w; w_index++) {
				out[index].values[h_index][w_index] = left->values[h_index][index] * right->values[h_index][w_index];
			}
		}
	}

	return out;
}

struct Matrix column_element_multiply(struct Matrix *matrix, struct Matrix *column_product) {
	int index;
	int h_index;
	int w_index;
	struct Matrix *tmp;
	struct Matrix out = create_matrix(matrix->h, column_product[0].w);

	for (index = 0; index < matrix->h; index++) {
		tmp = &column_product[index];
		for (w_index = 0; w_index < tmp->w; w_index++) {
			out.values[index][w_index] = 0.0;
			for (h_index = 0; h_index < tmp->h; h_index++) {
				out.values[index][w_index] += matrix->values[index][h_index] * tmp->values[h_index][w_index];
			}
		}
	}

	return out;
}

void randomize_matrix(struct Matrix *matrix, double range) {
	int h_index;
	int w_index;

	for (h_index = 0; h_index < matrix->h; h_index++)
		for (w_index = 0; w_index < matrix->w; w_index++)
			matrix->values[h_index][w_index] = (2.0 * range * (((double)rand()) / RAND_MAX)) - range;
}

void apply_function(struct Matrix *matrix, double (*handle)(double)) {
	int h_index;
	int w_index;
	struct Matrix output;

	for (h_index = 0; h_index < matrix->h; h_index++)
		for (w_index = 0; w_index < matrix->w; w_index++)
			matrix->values[h_index][w_index] = (*handle)(matrix->values[h_index][w_index]);
}

void delete_matrix(struct Matrix *matrix) {
	int h_index;
	int w_index;

	for (h_index = 0; h_index < matrix->h; h_index++) {
		free(matrix->values[h_index]);
	}
	free(matrix->values);

	return;
}

void copy_matrix(struct Matrix *matrix, struct Matrix *copy) {
	int h_index;
	int w_index;

	for (h_index = 0; h_index < copy->h; h_index++) {
		for (w_index = 0; w_index < copy->w; w_index++) {
			copy->values[h_index][w_index] = matrix->values[h_index][w_index];
		}
	}
}

struct Matrix hadamard(struct Matrix *left, struct Matrix *right, int put_left) {
	int h_index;
	int w_index;
	struct Matrix had;

	if (put_left) had = *left;
	else had = create_matrix(left->h, left->w);

	for (h_index = 0; h_index < left->h; h_index++) {
		for (w_index = 0; w_index < left->w; w_index++) {
			had.values[h_index][w_index] = left->values[h_index][w_index] * right->values[h_index][w_index];
		}
	}

	return had;
}

struct Matrix transpose(struct Matrix *matrix) {
	int h_index;
	int w_index;
	struct Matrix trans = create_matrix(matrix->w, matrix->h);

	trans.h = matrix->w;
	trans.w = matrix->h;

	for (h_index = 0; h_index < trans.h; h_index++) {
		for (w_index = 0; w_index < trans.w; w_index++) {
			trans.values[h_index][w_index] = matrix->values[w_index][h_index];
		}
	}

	return trans;
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
			term *= matrix->values[permute.options[w_index]][h_index];
			w_index++;
		}
		term *= counter % 2 == 1 ? -1.0 : 1.0;
		det += term;
		counter++;
	} while (next_permutation(&permute));

	return det;
}

int set_minor(struct Matrix *matrix, struct Matrix *minor, int h, int w) {
	int h_major;
	int w_major;
	int h_minor;
	int w_minor;

	if (matrix->h != minor->h + 1 || matrix->w != minor->w + 1)
		return 0;

	h_minor = 0;
	for (h_major = 0; h_major < matrix->h; h_major++) {
		if (h_major == h) continue;
		w_minor = 0;
		for (w_major = 0; w_major < matrix->w; w_major++) {
			if (w_major == w) continue;
			minor->values[h_minor][w_minor] = matrix->values[h_major][w_major];
			w_minor++;
		}
		h_minor++;
	}

	return 1;
}

void minors(struct Matrix *matrix) {
	double minor_det;
	int h_index;
	int w_index;
	struct Matrix minor = create_matrix(matrix->h - 1, matrix->w - 1);
	struct Matrix copy = create_matrix(matrix->h, matrix->w);

	for (h_index = 0; h_index < matrix->h; h_index++) {
		for (w_index = 0; w_index < matrix->w; w_index++) {
			set_minor(matrix, &minor, h_index, w_index);
			minor_det = determinant(&minor);
			copy.values[h_index][w_index] = minor_det;
		}
	}

	copy_matrix(&copy, matrix);
	delete_matrix(&copy);
	delete_matrix(&minor);
}

void adjugate_cofactors(struct Matrix *matrix) {
	int h_index;
	int w_index;
	double tmp;

	for (h_index = 0; h_index < matrix->h; h_index++) {
		for (w_index = h_index + 1; w_index < matrix->w; w_index++) {
			tmp = matrix->values[h_index][w_index];
			if ((w_index - h_index) % 2 == 1) {
				tmp *= -1.0;
				matrix->values[w_index][h_index] *= -1.0;
			}
			matrix->values[h_index][w_index] = matrix->values[w_index][h_index];
			matrix->values[w_index][h_index] = tmp;
		}
	}
}

int invert(struct Matrix *matrix) {
	int h_index;
	int w_index;
	double det = determinant(matrix);

	if (det > ZERO && det < -ZERO)
		return 0;

	minors(matrix);
	adjugate_cofactors(matrix);

	for (h_index = 0; h_index < matrix->h; h_index++) {
		for (w_index = 0; w_index < matrix->w; w_index++) {
			matrix->values[h_index][w_index] /= det;
		}
	}

	return 1;
}

void print_matrix(struct Matrix *matrix) {
	int h_index;
	int w_index;

	for (h_index = 0; h_index < matrix->h; h_index++) {
		for (w_index = 0; w_index < matrix->w; w_index++) {
			printf("%f    ", matrix->values[h_index][w_index]);
		}
		printf("\n");
	}
}

#endif

