#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _partition {
	int start_row;
	int start_col;
} patition_t;
typedef struct _matrix {
	int rows;
	int cols;
	int **entry;
} matrix_t;

matrix_t *init_matrix_with_data(int *data, int rows, int cols)
{
	int i, j;
	matrix_t *matrix;
	matrix = malloc(sizeof(matrix_t));
	matrix->entry = malloc(sizeof(int *)*rows);
	for (i = 0; i < rows; i++) {
		matrix->entry[i] = malloc(sizeof(int)*cols);
	}
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			matrix->entry[i][j] = data[j];
		}
		data += cols;
	}
	matrix->rows = rows;
	matrix->cols = cols;
	matrix->start_row = 0;
	matrix->start_col = 0;
	matrix->end_row   = rows - 1;
	matrix->end_col   = cols - 1;
	return matrix;
}

matrix_t *init_matrix_empty(int rows, int cols)
{
	int i;
	matrix_t *matrix;
	matrix = malloc(sizeof(matrix_t));
	matrix->entry = malloc(sizeof(int *)*rows);
	for (i = 0; i < rows; i++) {
		matrix->entry[i] = malloc(sizeof(int)*cols);
		memset(matrix->entry[i], 0, sizeof(int)*cols);
	}
	matrix->rows = rows;
	matrix->cols = cols;

	return matrix;
}

matrix_t *matrix_mutiply(matrix_t *a, matrix_t *b)
{
	int r, c, i;
	if (a->rows != b->cols)
		return NULL;
	matrix_t *result = init_matrix_empty(a->rows, b->cols);
	for (r = 0; r < a->rows; r++) {
		for (c = 0; c < b->cols; c++) {
			for (i = 0; i < a->cols; i++) {
				result->entry[r][c] += a->entry[r][i]* b->entry[i][c];
			}
		}
	}
	return result;
}

void print_matrix(matrix_t *matrix)
{
	int i, j;
	printf("Rows: %d Cols: %d\n", matrix->rows, matrix->cols);

	for (i = 0; i < matrix->rows; i++) {
		for (j = 0; j < matrix->cols; j++) {
			printf("%d ", matrix->entry[i][j]);
		}
		printf("\n");
	}
}

void dimension2_test(int array[][3], int rows, int cols)
{
	int i,j;

	printf("array size: %d\n", sizeof(array));
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			printf("%d ", array[j]);
		}
		array += cols;
		printf("\n");
	}
}

int get_matrix_item(matrix_t *matrix, int r, int c)
{
	return matrix->entry[matrix->start_row + r][matrix->start_col + c];
}

matrix_t *matrix_mutiply_recurency(matrix_t *a, matrix_t *b)
{
	patition_t partitiona1, partitiona2, partitiona3, partitiona4;
	patition_t partitionb1, partitionb2, partitionb3, partitionb4;
	if (partitionb1 == partitiona2)
	c1 = matrix_mutiply_recurency(partitiona1, partitionb1);
	c2 = matrix_mutiply_recurency(partitiona2, partitionb2);
	c3 = matrix_mutiply_recurency(partitiona3, partitionb3);
	c4 = matrix_mutiply_recurency(partitiona4, partitionb4);
	printf("[1][2]: %d\n", get_matrix_item(a, 1, 1));
	return NULL;
}

int main()
{
	int a[2][3] = {{1,2,3}, {4,5,6}};
	int b[][2] = {{7,8}, {9,10}, {11,12}};
	int c[] = {1,2,3,4,5,6,7,8,9,10};

	matrix_t *m_a = init_matrix_with_data((int *)a, 2, 3);
	matrix_t *m_b = init_matrix_with_data((int *)b, 3, 2);
	matrix_t *m_c = matrix_mutiply(m_a, m_b);
	/*
	print_matrix(m_c);
	printf("Array size: %d\n", sizeof(a[1]));
	dimension2_test(a, 2, 3);
	*/
	matrix_mutiply_recurency(m_a, m_b);
	return 0;
}