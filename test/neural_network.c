#include "matrix.h"
#include "nnopti.h"
#include "nnactiv.h"
#include "neural_network.h"
#include <stdio.h>
#include <stdlib.h>

#define SIZE 1

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
	int s;
	int wi;
	int index;
	int h_index;
	int w_index;
	double gran = 0.01;
	double diff = 0.05;
	int points = (int)(diff / gran) * 2;
	int mid = (int)(points / 2);
	double midf;
	int size[SIZE] = {2};
	double *slopes;
	double *outs;
	double *ins;
	float inter;
	int total;
	struct NeuralNetwork nn = create_feedforward_nn(2, 1, 1, size, &sigmoid);
	struct Matrix output;
	struct Matrix matrix = create_matrix(1, 2);
	struct NNParams params;
	struct Matrix csv;

	randomize_matrix(&matrix, 10.0);
	matrix.values[0][0] = 10.123456;
	// matrix.values[1][0] = 2.16;
	// matrix.values[2][0] = 3.13456;
	matrix.values[0][1] = 4.123456;
	// matrix.values[1][1] = 5.123456;
	// matrix.values[2][1] = 6.123456;
	// matrix.values[3][0] = 4.0;
	// matrix.values[3][1] = 5.0;

	initialize_weights(&nn);
	total = 0;
	for (index = 0; index < nn.layer_count + 1; index++) {
		total += nn.weights[index].h * nn.weights[index].w;
		apply_function(&nn.weights[index], &inc);
	}
	total *= 3;

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

	csv = create_matrix(points, total);
	for (h_index = 0; h_index < nn.weights[wi].h; h_index++) {
		for (w_index = 0; w_index < nn.weights[wi].w; w_index++) {
			nn.weights[wi].values[h_index][w_index] -= diff;
		}
	}
	for (index = 0; index < points; index++) {
		output = process_data(&nn, &matrix);
		i = 0;
		for (h_index = 0; h_index < nn.weights[wi].h; h_index++) {
			for (w_index = 0; w_index < nn.weights[wi].w; w_index++) {
				csv.values[index][i*3] = nn.weights[wi].values[h_index][w_index];
				csv.values[index][i*3+1] = output.values[0][0];
				nn.weights[wi].values[h_index][w_index] += gran;
				i += 1;
			}
		}
		delete_matrix(&output);
	}
	i = 0;
	for (h_index = 0; h_index < nn.weights[wi].h; h_index++) {
		for (w_index = 0; w_index < nn.weights[wi].w; w_index++) {
			nn.weights[wi].values[h_index][w_index] = csv.values[mid][i*3];
			i += 1;
		}
	}

	nn_quasi_newton_optimizer(&params);
	slopes = malloc(sizeof(double) * (params.total));
	outs = malloc(sizeof(double) * (params.total));
	ins = malloc(sizeof(double) * (params.total));
	for (i = 0; i < params.total; i++) {
		ins[i] = csv.values[mid][i*3];
		outs[i] = csv.values[mid][i*3+1];
	}
	for (i = 0; i < params.total; i++) {
		slopes[i] = params.primes[i].values[0][0];
		delete_matrix(&params.primes[i]);
	}
	for (i = 0; i < params.total; i++) {
		inter = outs[i] - ins[i] * slopes[i];
		for (index = 0; index < points; index++) {
			csv.values[index][i*3+2] = slopef(slopes[i], inter, csv.values[index][i*3]);
		}
		printf("%f,", outs[i]);
	}
	printf("\n");
	print_matrix(&matrix);
	free(slopes);
	free(outs);
	free(ins);

	to_csv(&csv);
	delete_matrix(&matrix);
	delete_matrix(&csv);
	delete_feedforward_nn(&nn);

	return 0;
}

