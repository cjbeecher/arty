#include "matrix.h"
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

struct Matrix *nn_first_der_activity(struct NeuralNetwork *nn, struct Matrix *input, struct *output) {
	int index;
	struct Matrix *der = malloc((struct Matrix) * sizeof(nn->layer_count));

	der[index] = create_matrix(input->h, nn->weights[index]->w);
	for (index = 1; index < nn->layer_count; index++) {
	}

	return der;
}

int nn_quasi_newton_optimizer(struct Params *params) {

	return 0;
}

#endif

