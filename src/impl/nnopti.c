#include "matrix.h"
#include "neural_network.h"

#ifndef P_NNOPTI_C
#define P_NNOPTI_C

// ap1 = z0p (a0p * w1)
struct Matrix activity_prime(struct Matrix *a, struct Matrix *a_prime, struct Matrix *w) {
	struct Matrix out = create_matrix(a->h, 
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

