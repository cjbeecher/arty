
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
void copy_matrix(struct Matrix *matrix, struct Matrix *copy);

double determinant(struct Matrix *matrix);
// Minor matrix is placed into minor
int set_minor(struct Matrix *matrix, struct Matrix *minor, int h, int w);
void minors(struct Matrix *matrix);
void adjugate_cofactors(struct Matrix *matrix);
int invert(struct Matrix *matrix);

void print_matrix(struct Matrix *matrix);

#endif

