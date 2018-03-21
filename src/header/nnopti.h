#include "matrix.h"
#include "neural_network.h"

#ifndef P_NNOPTI_H
#define P_NNOPTI_H

// For all optimzers, the following is true for returns
// 0 - Successful convergence
// 1 - Non-convergent
// 2 - Divergent solution
int nn_gradient_descent(struct NeuralNetwork *nn, struct Matrix *input, struct Matrix *output, double tol);

#endif

