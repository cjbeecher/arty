#include "stats.h"
#include <stdio.h>

int main() {
	int limit = 0;
	int index;
	struct Permute permute = make_permutator(4);

	while (next_permutation(&permute) && limit < 30) {
		printf("%i, %i : ", limit+1, permute.counter);
		for (index = 0; index < permute.size; index++)
			printf("%i,", permute.options[index]);
		printf(" = %i,%i", permute.swap[0], permute.swap[1]);
		printf("\n");
		limit++;
	}

	return 1;
}

