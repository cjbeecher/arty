#include "matrix.h"
#include "nnopti.h"
#include "nnactiv.h"
#include "neural_network.h"
#include <stdio.h>
#include <stdlib.h>


int main() {
	int layers[1] = {2};
	struct Matrix input;
	struct Matrix output;
	struct NeuralNetwork nn;

	nn = create_feedforward_nn(2, 1, 1, layers, &sigmoid);
	initialize_weights(&nn);
	input = create_matrix(1, 2);
	input.values[0][0] = 0.0;
	input.values[0][1] = 0.0;
	// print_matrix(&input);

	output = process_data(&nn, &input);
	print_matrix(&output);

	delete_feedforward_nn(&nn);
	delete_matrix(&input);
	delete_matrix(&output);

	return 0;
}

