#include "stats.h"
#include <stdlib.h>

#ifndef P_STATS_C
#define P_STATS_C

struct Permute create_permutator(int size) {
	int index;
	struct Permute permute;

	permute.size = size;
	permute.stack = 0;
	permute.iter = malloc(size * sizeof(int));
	for (index = 0; index < size - 1; index++)
		permute.iter[index] = 0;

	permute.options = malloc(size * sizeof(int));
	for (index = 0; index < size; index++)
		permute.options[index] = index;

	return permute;
}

int next_permutation(struct Permute *permute) {
	int tmp;

	if (permute->iter[permute->stack] < permute->stack) {
		if (permute->stack % 2 == 0) {
			tmp = permute->options[0];
			permute->options[0] = permute->options[permute->stack];
			permute->options[permute->stack] = tmp;
		}
		else {
			tmp = permute->options[permute->iter[permute->stack]];
			permute->options[permute->iter[permute->stack]] = permute->options[permute->stack];
			permute->options[permute->stack] = tmp;
		}
		permute->iter[permute->stack]++;
		permute->stack = 0;
		return 1;
	}
	else {
		permute->iter[permute->stack] = 0;
		permute->stack++;
		if (permute->stack < permute->size)
			return next_permutation(permute);
		else
			return 0;
	}
}

void delete_permutator(struct Permute *permute) {
	free(permute->options);
	free(permute->iter);
}

#endif

