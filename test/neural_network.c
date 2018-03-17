#include "matrix.h"
#include "nnopti.h"
#include "nnactiv.h"
#include "neural_network.h"
#include <stdio.h>
#include <stdlib.h>

#define SIZE 1
#define POINTS 100000

void to_csv(struct Matrix *m) {
	int size;
	int h_index;
	int w_index;
	int exp = 9;
	int v;
	char *output;

	size = m->h * m->w * exp;
	size += m->h * (m->w - 1);
	size += m->h;
	output = malloc(sizeof(char) * size);

	size = 0;
	for (h_index = 0; h_index < m->h; h_index++) {
		for (w_index = 0; w_index < m->w; w_index++) {
			snprintf(&output[size], exp, "%f", m->values[h_index][w_index]);
			size += exp - 1;
			output[size] = ',';
			size++;
		}
		output[size-1] = '\n';
	}
	output[size] = '\0';

	FILE *f;
	f = fopen("/home/cjbeecher/Documents/arty/test/data.csv", "w");
	fputs(output, f);
	fclose(f);

	free(output);
}

float slopef(float s, float x, float y, float in) {
	return s * (in - x) + y;
}

int main() {
	int i;
	int s;
	int wi;
	int index;
	int h_index;
	int w_index;
	int mid = (int)(POINTS / 2);
	float midf;
	int size[SIZE] = {2};
	float *slopes;
	float *outs;
	float *ins;
	struct NeuralNetwork nn = create_feedforward_nn(2, 1, 1, size, &sigmoid);
	struct Matrix output;
	struct Matrix matrix = create_matrix(1, 2);
	struct NNParams params;
	struct Matrix csv = create_matrix_zeroes(POINTS, 18);

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
					csv.values[i][s*3] = nn.weights[wi].values[h_index][w_index];
					csv.values[i][s*3+1] = output.values[0][0];
					csv.values[i][s*3+2] = 0.0;
					delete_matrix(&output);
				}
				s++;
			}
		}
	}

	s = 2;
	for (wi = 0; wi < nn.layer_count + 1; wi++) {
		for (h_index = 0; h_index < nn.weights[wi].h; h_index++) {
			for (w_index = 0; w_index < nn.weights[wi].w; w_index++) {
				midf = csv.values[mid][s-2];
				nn.weights[wi].values[h_index][w_index] = midf;
			}
		}
	}
	nn_quasi_newton_optimizer(&params);
	slopes = malloc(sizeof(float) * params.total);
	outs = malloc(sizeof(float) * params.total);
	ins = malloc(sizeof(float) * params.total);
	for (i = 0; i < params.total; i++) {
		ins[i] = csv.values[mid][i*3];
		outs[i] = csv.values[mid][i*3+1];
	}
	for (i = 0; i < params.total; i++) {
		slopes[i] = params.primes[i].values[0][0];
		delete_matrix(&params.primes[i]);
	}
	for (i = 0; i < params.total; i++) {
		for (index = 0; index < POINTS; index++) {
			csv.values[index][i*3+2] = slopef(slopes[i], ins[i], outs[i], csv.values[index][i*3]);
		}
	}
	free(slopes);
	free(outs);
	free(ins);

	to_csv(&csv);
	// print_matrix(&csv);
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

