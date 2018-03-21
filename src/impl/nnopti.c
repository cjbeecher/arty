#include "matrix.h"
#include "nnopti.h"
#include "nnactiv.h"
#include "neural_network.h"
#include <stdlib.h>
#include <stdio.h>

#ifndef P_NNOPTI_C
#define P_NNOPTI_C

// ap1 = z0p (a0pT * w1)
// struct Matrix *matrix, double (*handle)(double)
struct Matrix _activity_prime(struct Matrix *a, struct Matrix *a_prime, struct Matrix *w, double (*f_der)(double)) {
	int index;
	struct Matrix *term1;
	struct Matrix out;
	struct Matrix a_prime_trans = transpose(a_prime);
	struct Matrix z_prime = create_matrix(a->h, a->w);

	copy_matrix(a, &z_prime);
	apply_function(&z_prime, f_der);

	term1 = column_element_product(&a_prime_trans, w);
	out = column_element_multiply(&z_prime, term1);

	for (index = 0; index < a->h; index++) delete_matrix(&term1[index]);
	free(term1);
	delete_matrix(&a_prime_trans);
	delete_matrix(&z_prime);

	return out;
}

struct Matrix *_activities(struct NeuralNetwork *nn, struct Matrix *input) {
	int index;
	int count;
	struct Matrix a;
	struct Matrix *as;
	count = nn->layer_count;
	as = malloc(sizeof(struct Matrix) * count);

	as[0] = multiply_matrix(input, &nn->weights[0]);
	for (index = 1; index < count; index++) {
		a = create_matrix(as[index-1].h, as[index-1].w);
		copy_matrix(&as[index-1], &a);
		apply_function(&a, nn->activation_function);
		as[index] = multiply_matrix(&a, &nn->weights[index]);
		delete_matrix(&a);
	}

	return as;
}

struct Matrix _calc_prime(struct NeuralNetwork *nn, struct Matrix *as, struct Matrix *prime, int init) {
	int index;
	struct Matrix tmp;

	tmp = *prime;
	for (index = init; index < nn->layer_count; index++) {
		*prime = _activity_prime(&as[index], prime, &nn->weights[index+1], &sigmoid_deriv);
		delete_matrix(&tmp);
		tmp = *prime;
	}

	return *prime;
}

struct Matrix *_nn_prime(struct NeuralNetwork *nn, struct Matrix *input, struct Matrix *output, int total) {
	int index;
	int h_index;
	int w_index;
	int der_index;
	double (*active_der)(double);
	struct Matrix a;
	struct Matrix *der;
	struct Matrix *as; // Layer activity
	struct Matrix ap; // Layer activity prime
	struct Matrix wp; // Weight prime
	struct Matrix prime;

	active_der = &sigmoid_deriv;

	der = malloc(sizeof(struct Matrix) * total);
	as = _activities(nn, input);

	der_index = 0;
	for (index = 0; index < nn->layer_count + 1; index++) {
		wp = create_matrix_zeroes(nn->weights[index].h, nn->weights[index].w);
		for (h_index = 0; h_index < nn->weights[index].h; h_index++) {
			for (w_index = 0; w_index < nn->weights[index].w; w_index++) {
				wp.values[h_index][w_index] = 1.0;
				if (index == 0) {
					prime = multiply_matrix(input, &wp);
				}
				else {
					a = create_matrix(as[index-1].h, as[index-1].w);
					copy_matrix(&as[index-1], &a);
					apply_function(&a, nn->activation_function);
					prime = multiply_matrix(&a, &wp);
					delete_matrix(&a);
				}
				der[der_index] = _calc_prime(nn, as, &prime, index);
				wp.values[h_index][w_index] = 0.0;
				der_index++;
			}
		}
		delete_matrix(&wp);
	}

	return der;
}

int nn_quasi_newton_optimizer(struct NNParams *params) {
	int i;
	int p;
	int index;
	int h_index;
	int w_index;
	struct Matrix tmp;
	struct Matrix *prime;
	struct Matrix current;

	params->total = 0;
	for (index = 0; index < params->nn->layer_count + 1; index++)
		params->total += params->nn->weights[index].h * params->nn->weights[index].w;
	prime = _nn_prime(params->nn, params->input, params->output, params->total);
	params->primes = prime;

	i = 0;
	current = process_data(params->nn, params->input);
	for (index = 0; index < params->nn->layer_count + 1; index++) {
		for (h_index = 0; h_index < params->nn->weights[index].h; h_index++) {
			for (w_index = 0; w_index < params->nn->weights[index].w; w_index++) {
				prime = &params->primes[i];
				subtract_matrix(prime, params->output, 1);
				//tmp = subtract_matrix(&current, params->output, 0);
				//params->primes[i] = hadamard(&tmp, prime, 0);
				//delete_matrix(&tmp);
				i++;
			}
		}
	}

	return 0;
}

#endif

