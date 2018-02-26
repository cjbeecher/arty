#include "matrix.h"
#include "neural_network.h"

#ifndef P_NNOPTI_C
#define P_NNOPTI_C

int quasi_newton_optimizer(struct Params *params) {
	int index;
	int inter = params->nn->layer_count - 1;
	struct Matrix *activities = malloc(sizeof(struct Matrix) * size);
	struct Matrix *activity_primes = malloc(sizeof(struct Matrix) * size);

	for (index = 0; index < inter; index++) {
		params->nn->layer_count = index;
		activities[index] = process_data(params->nn, params->input);
	}
	params->nn->layer_count++;

	for (index = 0; index < inter; index++) {
		delete_matrix(activities[index]);
	}

	return 0;
}

#endif

