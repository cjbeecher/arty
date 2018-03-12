#include "matrix.h"
#include "nnopti.h"
#include "nnactiv.h"
#include "neural_network.h"
#include <stdio.h>

#define SIZE 1
#define POINTS 100000

int main() {
	int i;
	int s;
	int wi;
	int index;
	int h_index;
	int w_index;
	int size[SIZE] = {2};
	struct NeuralNetwork nn = create_feedforward_nn(2, 1, 1, size, &sigmoid);
	struct Matrix output;
	struct Matrix matrix = create_matrix(1, 2);
	struct NNParams params;
	struct Matrix csv = create_matrix_zeroes(POINTS, 12);

	matrix.values[0][0] = 10.123456;
	// matrix.values[1][0] = 2.16;
	// matrix.values[2][0] = 3.13456;
	matrix.values[0][1] = 4.123456;
	// matrix.values[1][1] = 5.123456;
	// matrix.values[2][1] = 6.123456;
	// matrix.values[3][0] = 4.0;
	// matrix.values[3][1] = 5.0;

	initialize_weights(&nn);

	// print_matrix(&matrix);
	// printf("\n");
	for (index = 0; index < SIZE + 1; index++) {
		// print_matrix(&nn.weights[index]);
		// printf("\n");
	}
	output = process_data(&nn, &matrix);
	// print_matrix(&output);

	params.input = &matrix;
	params.output = &output;
	params.nn = &nn;

	s = 0;
	delete_matrix(&output);
	for (wi = 0; wi < nn.layer_count + 1; wi++) {
		for (h_index = 0; h_index < nn.weights[wi].h; h_index++) {
			for (w_index = 0; w_index < nn.weights[wi].w; w_index++) {
				nn.weights[wi].values[h_index][w_index] -= 0.00001 * POINTS;
				for (i = 0; i < POINTS; i++) {
					nn.weights[wi].values[h_index][w_index] += 0.00001;
					output = process_data(&nn, &matrix);
					csv.values[i][s*2] = output.values[0][0];
					delete_matrix(&output);
				}
				s++;
			}
		}
	}
	print_matrix(&csv);
	nn_quasi_newton_optimizer(&params);
	for (index = 0; index < params.total; index++) {
		// print_matrix(&params.primes[index]);
		// printf("\n");
		delete_matrix(&params.primes[index]);
	}
	delete_matrix(&matrix);
	delete_matrix(&csv);
	delete_feedforward_nn(&nn);

	return 0;
}

