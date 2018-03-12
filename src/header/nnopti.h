#include "matrix.h"
#include "neural_network.h"

#ifndef P_NNOPTI_H
#define P_NNOPTI_H

struct NNParams {
	int total;
	struct Matrix *input;
	struct Matrix *output;
	struct NeuralNetwork *nn;
	struct Matrix *primes;
};

// For all optimzers, the following is true for returns
// 0 - Successful convergence
// 1 - Non-convergent
// 2 - Divergent solution
int nn_quasi_newton_optimizer(struct NNParams *params);

#endif

