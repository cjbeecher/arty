#include "matrix.h"
#include <stdio.h>

int main() {
	struct Matrix matrix = create_matrix(4, 4, 1);

	*matrix.values[0][0] = 10.123456;
	*matrix.values[1][0] = 2.16;
	*matrix.values[2][0] = 3.13456;
	*matrix.values[0][1] = 4.123456;
	*matrix.values[1][1] = 5.123456;
	*matrix.values[2][1] = 6.123456;
	*matrix.values[0][2] = 7.123456;
	*matrix.values[1][2] = 8.156;
	*matrix.values[2][2] = 109.123456;
	*matrix.values[0][3] = 1.0;
	*matrix.values[1][3] = 2.0;
	*matrix.values[2][3] = 3.0;
	*matrix.values[3][0] = 4.0;
	*matrix.values[3][1] = 5.0;
	*matrix.values[3][2] = 6.0;
	*matrix.values[3][3] = 7.0;
	print_matrix(&matrix);
	printf("%f\n", determinant(&matrix));

	delete_matrix(&matrix);
	return 0;
}

