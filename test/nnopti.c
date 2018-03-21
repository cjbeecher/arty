#include "matrix.h"
#include "nnopti.h"
#include "nnactiv.h"
#include "neural_network.h"
#include <stdio.h>
#include <stdlib.h>

#define LAYERS 1
#define LAYER_SIZES {2}
#define INPUT 2
#define INPUT_ROWS 4
#define OUTPUT 1
#define DIFF 0.05
#define GRAN 0.0001


int main() {
	int index;
	int h_index;
	int w_index;
	int layer_sizes[LAYERS] = LAYER_SIZES;
	struct NeuralNetwork nn;
	struct Matrix input;
	struct Matrix output;
	struct NNParams params;

	nn = create_feedforward_nn(INPUT, OUTPUT, LAYERS, layer_sizes, &sigmoid);
	input = create_matrix(INPUT_ROWS, INPUT);
	input[0][0] = 0.0;
	input[0][1] = 0.0;
	input[1][0] = 0.0;
	input[1][1] = 1.0;
	input[2][0] = 0.0;
	input[2][1] = 1.0;
	input[3][0] = 1.1;
	input[3][1] = 1.1;
	output = create_matrix(INPUT_ROWS, OUTPUT);
	output.values[0][0] = 0.0;
	output.values[1][0] = 1.0;
	output.values[2][0] = 1.0;
	output.values[3][0] = 0.0;
	params.input = &input;
	params.output = &output;
	params.nn = &nn;

	nn_quasi_newton_optimizer(&params);

	delete_feedforward_nn(&nn);
	delete_matrix(&input);
	delete_matrix(&output);

	return 0;
}

