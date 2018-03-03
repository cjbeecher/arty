#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	int index;
	struct Matrix *column_product;
	struct Matrix fin;
	struct Matrix matrix = create_matrix(4, 4);
	struct Matrix right = create_matrix(4, 4);

	matrix.values[0][0] = 10.123456;
	matrix.values[1][0] = 2.16;
	matrix.values[2][0] = 3.13456;
	matrix.values[0][1] = 4.123456;
	matrix.values[1][1] = 5.123456;
	matrix.values[2][1] = 6.123456;
	matrix.values[0][2] = 7.123456;
	matrix.values[1][2] = 8.156;
	matrix.values[2][2] = 109.123456;
	matrix.values[0][3] = 1.0;
	matrix.values[1][3] = 2.0;
	matrix.values[2][3] = 3.0;
	matrix.values[3][0] = 4.0;
	matrix.values[3][1] = 5.0;
	matrix.values[3][2] = 6.0;
	matrix.values[3][3] = 7.0;

	right.values[0][0] = 1.0;
	right.values[0][1] = 2.0;
	right.values[0][2] = 3.0;
	right.values[0][3] = 4.0;
	right.values[1][0] = 8.0;
	right.values[1][1] = 9.0;
	right.values[1][2] = 10.0;
	right.values[1][3] = 11.0;
	right.values[2][0] = 15.0;
	right.values[2][1] = 16.0;
	right.values[2][2] = 17.0;
	right.values[2][3] = 18.0;
	right.values[3][0] = 22.0;
	right.values[3][1] = 23.0;
	right.values[3][2] = 24.0;
	right.values[3][3] = 25.0;

	subtract_matrix(&matrix, &right, 1);
	invert(&matrix);
	print_matrix(&matrix);
	transpose(&matrix);
	printf("\n");
	print_matrix(&matrix);

	column_product = column_element_product(&matrix, &right);
	fin = column_element_multiply(&matrix, column_product);
	printf("----------\n");
	print_matrix(&fin);
	printf("==========\n");
	for (index = 0; index < matrix.w; index++) {
		print_matrix(&column_product[index]);
		delete_matrix(&column_product[index]);
		printf("\n");
	}
	free(column_product);

	delete_matrix(&matrix);
	delete_matrix(&right);

	return 0;
}

