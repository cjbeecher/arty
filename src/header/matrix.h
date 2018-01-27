
#ifndef P_MATRIX_H
#define P_MATRIX_H

struct Matrix {
	double ***values;
	int is_populated;
	int w;
	int h;
};

struct Matrix create_matrix(int h, int w, int populate);
void delete_matrix(struct Matrix *matrix);

double determinant(struct Matrix *matrix);

void print_matrix(struct Matrix *matrix);

#endif

