#include "matrix.h"
#include "nnopti.h"
#include "nnactiv.h"
#include "neural_network.h"
#include <stdlib.h>

#ifndef P_NNOPTI_C
#define P_NNOPTI_C

// ap1 = z0p (a0pT * w1)
// struct Matrix *matrix, double (*handle)(double)
struct Matrix activity_prime(struct Matrix *a, struct Matrix *a_prime, struct Matrix *w, double (*f_der)(double)) {
	int index;
	struct Matrix *term1;
	struct Matrix out;
	struct Matrix a_prime_trans = transpose(a_prime);
	struct Matrix z_prime = create_matrix(a->h, a->w);
	copy_matrix(a, &z_prime);
	apply_function(&z_prime, f_der);

	term1 = column_element_product(&a_prime_trans, w);
	out = column_element_multiply(&z_prime, term1);

	for (index = 0; index < a->h; index++) delete_matrix(&term1[index]);
	free(term1);
	delete_matrix(&a_prime_trans);
	delete_matrix(&z_prime);

	return out;
}

struct Matrix *activities(struct NeuralNetwork *nn, struct Matrix *input) {
	int index;
	struct Matrix *as;
	struct Matrix tmp_z;

	as = malloc(sizeof(struct Matrix) * nn->layer_count);
	as[0] = create_matrix(input->h, input->w);
	copy_matrix(input, &as[0]);
	for (index = 1; index < nn->layer_count; index++) {
		tmp_z = create_matrix(as[index-1].h, as[index-1].w);
		copy_matrix(&as[index-1], &tmp_z);
		apply_function(&tmp_z, nn->activation_function);
		as[index] = multiply_matrix(&tmp_z, &nn->weights[index-1]);
		delete_matrix(&tmp_z);
	}

	return as;
}

struct Matrix *nn_first_der_activity(struct NeuralNetwork *nn, struct Matrix *input, struct Matrix *output) {
	int index;
	int total;
	double (*active_der)(double);
	struct Matrix *as; // Activities array
	struct Matrix *der;

	active_der = &sigmoid_deriv;

	total = 0;
	for (index = 0; index < nn->layer_count + 1; index++)
		total += nn->weights[index].h * nn->weights[index].w;

	der = malloc(sizeof(struct Matrix) * total);
	as = activities(nn, input);

	for (index = 0; index < nn->layer_count + 1; index++) {
	}

	return der;
}

int nn_quasi_newton_optimizer(struct NNParams *params) {

	return 0;
}

#endif

