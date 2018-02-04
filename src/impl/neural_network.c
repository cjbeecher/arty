#include "neural_network.h"
#include "matrix.h"
#include <stdlib.h>

#ifndef P_NN_C
#define P_NN_C

struct NeuralNetwork create_multilayer_perceptron(int input, int output, int layers, int *layer_sizes) {
	int index;
	int size_index;
	struct Perceptron *pre_p;
	struct Perceptron *cur_p;
	struct NeuralNetwork nn;

	nn.input_size = input;
	nn.input = malloc(sizeof(struct Perceptron) * input);

	pre_p = (struct Perceptron *)nn.input;
	for (index = 0; index < layers; index++) {
		for (size_index = 0; size_index < layer_sizes[index]; size_index++) {
			;
		}
	}

	return nn;
}

void delete_multilayer_perceptron(struct NeuralNetwork *nn) {
	int index;

	for (index = 0; index < nn->input_size; index++) {
	}
}

#endif

