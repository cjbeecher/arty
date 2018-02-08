
#ifndef P_NN_H
#define P_NN_H

struct NeuralNetwork {
	int input;
	int output;
	int layer_count;
	// Columns are activation/activity of next layer
	// Weight columns are then tied to single node next layer
	struct Matrix *weights;
};

struct NeuralNetwork create_feedforward_nn(int input, int output, int layers, int *layer_sizes);
void delete_feedforward_nn(struct NeuralNetwork *nn);

void initialize_weights(struct NeuralNetwork *nn);

#endif

