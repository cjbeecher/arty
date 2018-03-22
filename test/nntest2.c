#include "matrix.h"
#include "nnopti.h"
#include "nnactiv.h"
#include "neural_network.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main() {
	int index;
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

	for (index = 0; index < 100000; index++) {
		output = process_data(&nn, &input);
		delete_matrix(&output);
		sleep(1);
		printf("= %i\n", index+1);
	}
	// print_matrix(&output);

	delete_feedforward_nn(&nn);
	// delete_matrix(&input);

	return 0;
}

