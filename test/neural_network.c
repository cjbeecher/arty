#include "matrix.h"
#include "nnopti.h"
#include "nnactiv.h"
#include "neural_network.h"
#include <stdio.h>
#include <stdlib.h>

#define LAYERS 1
#define LAYER_SIZES {2}
#define INPUT 2
#define INPUT_ROWS 1
#define OUTPUT 1
#define DIFF 0.05
#define GRAN 0.0001


void to_csv(struct Matrix *m) {
	int size;
	int h_index;
	int w_index;
	int exp = 16;
	int v;
	char *output;

	size = m->h * m->w * exp;
	size += m->h * (m->w - 1);
	size += m->h;
	output = malloc(sizeof(char) * size);

	size = 0;
	for (h_index = 0; h_index < m->h; h_index++) {
		for (w_index = 0; w_index < m->w; w_index++) {
			snprintf(&output[size], exp, "%.30f", m->values[h_index][w_index]);
			size += exp - 1;
			output[size] = ',';
			size++;
		}
		output[size-1] = '\n';
	}
	output[size-1] = '\0';

	FILE *f;
	f = fopen("/home/cjbeecher/Documents/arty/test/data.csv", "w");
	fputs(output, f);
	fclose(f);

	free(output);
}

double slopef(double s, double inter, double in) {
	return s * in + inter;
}

double inc(double x) {
	return x * 1.0;
}

int main() {
	int i;
	int wi;
	int mid;
	int index;
	int total;
	int points;
	int h_index;
	int w_index;
	int layer_sizes[LAYERS] = LAYER_SIZES;
	double tmp;
	double inter;
	struct NeuralNetwork nn;
	struct Matrix csv;
	struct Matrix input;
	struct Matrix output;
	struct NNParams params;

	nn = create_feedforward_nn(INPUT, OUTPUT, LAYERS, layer_sizes, &sigmoid);
	input = create_matrix(INPUT_ROWS, INPUT);
	randomize_matrix(&input, 10.0);
	total = 0;
	for (index = 0; index < LAYERS + 1; index++) total += nn.weights[index].h * nn.weights[index].w;
	points = (int)(DIFF * 2 / GRAN);
	mid = (int)(points / 2);
	csv = create_matrix(points, total * 3);

	initialize_weights(&nn);

	i = 0;
	for (wi = 0; wi < LAYERS + 1; wi++) {
		for (h_index = 0; h_index < nn.weights[wi].h; h_index++) {
			for (w_index = 0; w_index < nn.weights[wi].w; w_index++) {
				nn.weights[wi].values[h_index][w_index] -= DIFF;
				for (index = 0; index < points; index++) {
					csv.values[index][i*3] = nn.weights[wi].values[h_index][w_index];
					nn.weights[wi].values[h_index][w_index] += GRAN;
				}
				i += 1;
			}
		}
	}
	i = 0;
	for (wi = 0; wi < LAYERS + 1; wi++) {
		for (h_index = 0; h_index < nn.weights[wi].h; h_index++) {
			for (w_index = 0; w_index < nn.weights[wi].w; w_index++) {
				nn.weights[wi].values[h_index][w_index] = csv.values[mid][i*3];
				i++;
			}
		}
	}
	i = 0;
	for (wi = 0; wi < LAYERS + 1; wi++) {
		for (h_index = 0; h_index < nn.weights[wi].h; h_index++) {
			for (w_index = 0; w_index < nn.weights[wi].w; w_index++) {
				tmp = nn.weights[wi].values[h_index][w_index];
				for (index = 0; index < points; index++) {
					nn.weights[wi].values[h_index][w_index] = csv.values[index][i*3];
					output = process_data(&nn, &input);
					csv.values[index][i*3+1] = output.values[0][0];
					delete_matrix(&output);
				}
				nn.weights[wi].values[h_index][w_index] = tmp;
				i++;
			}
		}
	}

	params.input = &input;
	params.nn = &nn;
	nn_quasi_newton_optimizer(&params);
	for (index = 0; index < total; index++) {
		tmp = params.primes[index].values[0][0];
		inter = csv.values[mid][index*3+1] - tmp * csv.values[mid][index*3];
		for (i = 0; i < points; i++) {
			csv.values[i][index*3+2] = slopef(tmp, inter, csv.values[i][index*3]);
		}
	}
	to_csv(&csv);

	printf("== %i\n", mid);
	print_matrix(&input);
	printf("\n");
	for (index = 0; index < params.nn->layer_count + 1; index++) {
		print_matrix(&params.nn->weights[index]);
		printf("\n");
	}
	printf("====\n");
	for (index = 0; index < params.total; index++)
		print_matrix(&params.primes[index]);
	printf("\n");

	delete_feedforward_nn(&nn);
	delete_matrix(&input);
	delete_matrix(&csv);
	for (index = 0; index < total; index++) delete_matrix(&params.primes[index]);
	free(params.primes);

	return 0;
}

