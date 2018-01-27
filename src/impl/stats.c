#include "stats.h"
#include <stdlib.h>

#ifndef P_STATS_C
#define P_STATS_C

struct Permute make_permutator(int size) {
	int index;
	struct Permute permute;

	permute.swap[0] = 0;
	permute.swap[1] = 0;
	permute.size = size;
	permute.counter = size;

	permute.options = malloc(size * sizeof(int));
	for (index = 0; index < size; index++)
		permute.options[index] = index;

	return permute;
}

int next_permutation(struct Permute *permute) {
	int tmp;
	int can_continue = 1;

	permute->swap[1]++;
	if (permute->swap[1] == permute->size) {
		permute->swap[0]++;
		permute->swap[0] %= permute->size - 1;
		permute->swap[1] = permute->swap[0] + 1;
		permute->swap[1] %= permute->size;
	}

	tmp = permute->options[permute->swap[0]];
	permute->options[permute->swap[0]] = permute->options[permute->swap[1]];
	permute->options[permute->swap[1]] = tmp;

	if (permute->swap[0] == 0 && permute->swap[1] == 1)
		permute->counter--;
	can_continue = permute->counter >= 0;

	return can_continue;
}

void delete_permutator(struct Permute *permute) {
	free(permute->options);
}

#endif

