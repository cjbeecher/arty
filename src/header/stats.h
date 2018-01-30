
#ifndef P_STATS_H
#define P_STATS_H

struct Permute {
	int *options;
	int size;
	int stack;
	int *iter;
};

struct Permute create_permutator(int size);
int next_permutation(struct Permute *permute);
void delete_permutator(struct Permute *permute);

#endif

