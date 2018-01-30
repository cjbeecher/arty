#include "stats.h"
#include <stdio.h>

int main() {
	int limit = 0;
	int index;
	struct Permute permute = create_permutator(4);

	do {
		printf("%i, %i : ", limit+1, permute.stack);
		for (index = 0; index < permute.size; index++)
			printf("%i,", permute.options[index]);
		printf(" = %i,%i", permute.iter[permute.stack], permute.stack);
		printf("\n");
		limit++;
	} while (next_permutation(&permute) && limit < 30);

	return 1;
}

