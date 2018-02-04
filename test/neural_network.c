#include "neural_network.h"

int main() {
	int size[1] = {2};
	struct NeuralNetwork nn = create_multilayer_perceptron(2, 1, 1, size);

	return 0;
}

