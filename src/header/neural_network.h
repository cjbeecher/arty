#include "matrix.h"

#ifndef P_NN_H
#define P_NN_H

// weights and perceptrons are inputs
struct Perceptron {
	double activation;
	int weights_size;
	double *weights;
	int next_size;
	struct Perceptron *perceptrons;
};

struct NeuralNetwork {
	int input_size;
	struct Perceptrons *inputs;
	int output_size;
};

struct NeuralNetwork create_multilayer_perceptron(int input, int output, int layers, int *layer_sizes);
void delete_multilayer_perceptron(struct NeuralNetwork *nn);

#endif

