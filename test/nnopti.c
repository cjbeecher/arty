#include "matrix.h"
#include "nnopti.h"
#include "nnactiv.h"
#include "neural_network.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LAYERS 1
#define LAYER_SIZES {2}
#define INPUT 2
#define INPUT_ROWS 4
#define OUTPUT 1
#define DIFF 0.05
#define GRAN 0.0001
#define TOL 0.05


int main() {
	int index;
	int h_index;
	int w_index;
	int layer_sizes[LAYERS] = LAYER_SIZES;
	struct NeuralNetwork nn;
	struct Matrix input;
	struct Matrix output;
	struct Matrix adjusted;

	nn = create_feedforward_nn(INPUT, OUTPUT, LAYERS, layer_sizes, &sigmoid);
	initialize_weights(&nn);
	input = create_matrix(INPUT_ROWS, INPUT);
	input.values[0][0] = 0.0;
	input.values[0][1] = 0.0;
	input.values[1][0] = 0.0;
	input.values[1][1] = 1.0;
	input.values[2][0] = 0.0;
	input.values[2][1] = 1.0;
	input.values[3][0] = 1.1;
	input.values[3][1] = 1.1;
	output = create_matrix(INPUT_ROWS, OUTPUT);
	output.values[0][0] = 0.0;
	output.values[1][0] = 1.0;
	output.values[2][0] = 1.0;
	output.values[3][0] = 0.0;

	for (index = 0; index < 1000; index++) {
		nn_gradient_descent(&nn, &input, &output, TOL);
		printf("= %i\n", index+1);
		sleep(1);
	}
	adjusted = process_data(&nn, &input);
	print_matrix(&adjusted);

	delete_feedforward_nn(&nn);
	delete_matrix(&input);
	delete_matrix(&output);
	delete_matrix(&adjusted);

	printf("Iterations: %i\n", index);

	return 0;
}

