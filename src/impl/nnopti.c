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

void _calc_prime(struct NeuralNetwork *nn, struct Matrix *as, struct Matrix *prime, int init) {
	int index;
	struct Matrix tmp;

	for (index = init; index < nn->layer_count; index++) {
		tmp = _activity_prime(&as[index], prime, &nn->weights[index+1], &sigmoid_deriv);
		copy_matrix(&tmp, prime);
		delete_matrix(&tmp);
	}
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
					der[der_index] = multiply_matrix(input, &wp);
				}
				else {
					a = create_matrix(as[index-1].h, as[index-1].w);
					copy_matrix(&as[index-1], &a);
					apply_function(&a, nn->activation_function);
					der[der_index] = multiply_matrix(&a, &wp);
					delete_matrix(&a);
				}
				_calc_prime(nn, as, &der[der_index], index);
				wp.values[h_index][w_index] = 0.0;
				der_index++;
			}
		}
		delete_matrix(&wp);
	}
	for (index = 0; index < nn->layer_count; index++)
		delete_matrix(&as[index]);
	free(as);

	return der;
}

struct Matrix *_calc_prime_err(struct NeuralNetwork *nn, struct Matrix *input, struct Matrix *output, int total) {
	int i;
	int index;
	int h_index;
	int w_index;
	struct Matrix tmp;
	struct Matrix *prime;
	struct Matrix *primes;
	struct Matrix current;

	primes = _nn_prime(nn, input, output, total);

	i = 0;
	current = process_data(nn, input);
	for (index = 0; index < nn->layer_count + 1; index++) {
		for (h_index = 0; h_index < nn->weights[index].h; h_index++) {
			for (w_index = 0; w_index < nn->weights[index].w; w_index++) {
				prime = &primes[i];
				subtract_matrix(prime, output, 1);
				tmp = subtract_matrix(&current, output, 0);
				hadamard(prime, &tmp, 1);
				delete_matrix(&tmp);
				i++;
			}
		}
	}
	delete_matrix(&current);

	return primes;
}

void _delete_primes(struct Matrix *primes, int total) {
	int index;

	for (index = 0; index < total; index++) {
		delete_matrix(&primes[index]);
	}
}

double _avg_err(struct Matrix *adjusted, struct Matrix *output) {
	int h_index;
	int w_index;
	double err;
	double tmp = 0.0;
	struct Matrix diff;

	diff = subtract_matrix(adjusted, output, 1);
	for (h_index = 0; h_index < adjusted->h; h_index++) {
		for (w_index = 0; w_index < adjusted->w; w_index++) {
			tmp = diff.values[h_index][w_index];
			tmp = tmp < 0.0 ? -1.0 * tmp : tmp;
			err += tmp;
		}
	}

	return err / (diff.h * diff.w);
}

int nn_gradient_descent(struct NeuralNetwork *nn, struct Matrix *input, struct Matrix *output, double tol) {
	int i;
	int col;
	int row;
	int iter;
	int index;
	int total;
	int h_index;
	int w_index;
	double lr = 1.0;
	double err;
	struct Matrix *primes;
	struct Matrix adjusted;

	total = 0;
	for (index = 0; index < nn->layer_count + 1; index++)
		total += nn->weights[index].h * nn->weights[index].w;
	total = total;

	for (iter = 0; iter < 1000000; iter++) {
		primes = _calc_prime_err(nn, input, output, total);
		i = 0;
		for (index = 0; index < nn->layer_count + 1; index++) {
			for (h_index = 0; h_index < nn->weights[index].h; h_index++) {
				for (w_index = 0; w_index < nn->weights[index].w; w_index++) {
					for (row = 0; row < output->h; row++) {
						for (col = 0; col < output->w; col++) {
							nn->weights[index].values[h_index][w_index] += primes[i].values[row][col] * lr;
						}
					}
				}
			}
		}
		adjusted = process_data(nn, input);
		err = _avg_err(&adjusted, output);
		delete_matrix(&adjusted);
		_delete_primes(primes, total);
		free(primes);
		if (err <= tol) break;
	}

	return iter;
}

#endif

