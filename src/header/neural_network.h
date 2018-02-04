
#ifndef P_NN_H
#define P_NN_H

struct NeuralNetwork {
	int input_size;
	struct Perceptron *input;
	int output_size;
	struct Perceptron *output;
};

struct NeuralNetwork create_multilayer_perceptron(int input, int output, int layers, int *layer_sizes);

#endif

