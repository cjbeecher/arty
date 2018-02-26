#include <math.h>

#ifndef P_NNACTIV_C
#define P_NNACTIV_C

double sigmoid(double value) {
	return 1 / (1 + exp(-1.0 * value));
}

double sigmoid_deriv(double value) {
	return sigmoid(value) * (1.0 - sigmoid(value));
}

#endif

