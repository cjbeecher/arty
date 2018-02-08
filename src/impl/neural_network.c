#include "neural_network.h"
#include "matrix.h"
#include <time.h>
#include <stdlib.h>

#ifndef P_NN_C
#define P_NN_C

#define RADIAL_RANGE 1

struct NeuralNetwork create_feedforward_nn(int input, int output, int layers, int *layer_sizes) {
	int index;
	int prev_size;
	struct NeuralNetwork nn;

	nn.input = input;
	nn.output = output;
	nn.layer_count = layers;
	nn.weights = malloc(layers * sizeof(struct Matrix));

	prev_size = input;
	for (index = 0; index < layers; index++) {
		nn.weights[index] = create_matrix(prev_size, layer_sizes[index], 1);
		prev_size = layer_sizes[index];
	}

	return nn;
}

void delete_feedforward_nn(struct NeuralNetwork *nn) {
	int index;

	for (index = 0; index < nn->layer_count; index++)
		delete_matrix(&nn->weights[index]);
	free(nn->weights);
}

void initialize_weights(struct NeuralNetwork *nn) {
	int index;
	srand(time(NULL));

	for (index = 0; index < nn->layer_count; index++)
		randomize_matrix(&nn->weights[index], RADIAL_RANGE);
}

#endif

