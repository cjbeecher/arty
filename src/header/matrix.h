
#ifndef P_MATRIX_H
#define P_MATRIX_H

struct Matrix {
	double **values;
	int w;
	int h;
};

struct Matrix create_matrix(int h, int w);
void delete_matrix(struct Matrix *matrix);
void copy_matrix(struct Matrix *matrix, struct Matrix *copy);

struct Matrix multiply_matrix(struct Matrix *left, struct Matrix *right);
struct Matrix add_matrix(struct Matrix *left, struct Matrix *right, int put_left);
struct Matrix subtract_matrix(struct Matrix *left, struct Matrix *right, int put_left);

// Tuple of matrices in which the tuple size = left->w
// If left->h != right->h then 0 is returned
struct Matrix *column_element_product(struct Matrix *left, struct Matrix *right);
struct Matrix column_element_multiply(struct Matrix *matrix, struct Matrix *column_product);

void randomize_matrix(struct Matrix *matrix, double range);
void apply_function(struct Matrix *matrix, double (*handle)(double));

void transpose(struct Matrix *matrix);
double determinant(struct Matrix *matrix);
// Minor matrix is placed into minor
int set_minor(struct Matrix *matrix, struct Matrix *minor, int h, int w);
void minors(struct Matrix *matrix);
void adjugate_cofactors(struct Matrix *matrix);
int invert(struct Matrix *matrix);

void print_matrix(struct Matrix *matrix);

#endif

