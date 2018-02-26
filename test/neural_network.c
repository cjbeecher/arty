#include "matrix.h"
#include "nnactiv.h"
#include "neural_network.h"
#include <stdio.h>

#define SIZE 1

int main() {
	int index;
	int size[SIZE] = {2};
	struct NeuralNetwork nn = create_feedforward_nn(2, 1, 1, size, &sigmoid);
	struct Matrix output;
	struct Matrix matrix = create_matrix(4, 2);

	matrix.values[0][0] = 10.123456;
	matrix.values[1][0] = 2.16;
	matrix.values[2][0] = 3.13456;
	matrix.values[0][1] = 4.123456;
	matrix.values[1][1] = 5.123456;
	matrix.values[2][1] = 6.123456;
	matrix.values[3][0] = 4.0;
	matrix.values[3][1] = 5.0;

	initialize_weights(&nn);

	print_matrix(&matrix);
	printf("\n");
	for (index = 0; index < SIZE + 1; index++) {
		print_matrix(&nn.weights[index]);
		printf("\n");
	}
	output = process_data(&nn, &matrix);
	print_matrix(&output);

	printf("\n");
	delete_matrix(&output);
	delete_feedforward_nn(&nn);

	return 0;
}

