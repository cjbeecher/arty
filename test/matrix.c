#include "matrix.h"
#include <stdio.h>

int main() {
	struct Matrix matrix = create_matrix(5, 4, 1);
	struct Matrix right = create_matrix(4, 6, 1);
	struct Matrix output;

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
	*matrix.values[4][0] = 8.0;
	*matrix.values[4][1] = 9.0;
	*matrix.values[4][2] = 10.0;
	*matrix.values[4][3] = 11.0;

	*right.values[0][0] = 1.0;
	*right.values[0][1] = 2.0;
	*right.values[0][2] = 3.0;
	*right.values[0][3] = 4.0;
	*right.values[0][4] = 5.0;
	*right.values[0][5] = 6.0;
	*right.values[1][0] = 8.0;
	*right.values[1][1] = 9.0;
	*right.values[1][2] = 10.0;
	*right.values[1][3] = 11.0;
	*right.values[1][4] = 12.0;
	*right.values[1][5] = 7.0;
	*right.values[2][0] = 15.0;
	*right.values[2][1] = 16.0;
	*right.values[2][2] = 17.0;
	*right.values[2][3] = 18.0;
	*right.values[2][4] = 19.0;
	*right.values[2][5] = 8.0;
	*right.values[3][0] = 22.0;
	*right.values[3][1] = 23.0;
	*right.values[3][2] = 24.0;
	*right.values[3][3] = 25.0;
	*right.values[3][4] = 26.0;
	*right.values[3][5] = 9.0;

	output = multiply_matrix(&matrix, &right);
	print_matrix(&output);

	delete_matrix(&matrix);
	delete_matrix(&right);
	delete_matrix(&output);
	return 0;
}

