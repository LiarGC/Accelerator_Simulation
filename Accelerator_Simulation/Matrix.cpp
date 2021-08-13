#include "Matrix.h"
#include <iostream>
using namespace std;

Matrix::Matrix(unsigned int row,unsigned int col)
{
	this->row = row; this->col = col;
	matrix_buffer = (double*)mkl_malloc(row * col * sizeof(double), 64);
	if (matrix_buffer == NULL) {
		printf("ERROR: Can't allocate memory for matrices. Aborting... \n\n");
		mkl_free(matrix_buffer);
		return;
	}
}

Matrix::Matrix(const Matrix& m)
{
	this->row = m.row; this->col = m.col;
	matrix_buffer = (double*)mkl_malloc(row * col * sizeof(double), 64);
	if (matrix_buffer == NULL) {
		printf("ERROR: Can't allocate memory for matrices. Aborting... \n\n");
		mkl_free(matrix_buffer);
		return;
	}
	if (this->matrix_buffer == m.matrix_buffer) return;

	memcpy(this->matrix_buffer, m.matrix_buffer, row * col * sizeof(double));
}

Matrix::~Matrix()
{
	mkl_free(matrix_buffer);
}

void Matrix::InputMatrixBuffer(double* buffer, unsigned int sizeof_buffer)
{
	unsigned int length = sizeof_buffer / sizeof(double);
	for (unsigned int i = 0; i < row * col; i++) {
		if (i < length) matrix_buffer[i] = buffer[i];
		else matrix_buffer[i] = 0;
	}
}

void Matrix::SetMartrixElement(unsigned int row, unsigned int col, double num)
{
	if (row > this->row or col > this->col) {
		printf("SetMartrixElement falled!\nMatrix size exceeded!\n");
		return;
	}
	matrix_buffer[row * this->col + col] = num;
}

void Matrix::col_stack(const Matrix& m)
{
	if (this->row != m.row) {
		printf("col_stack falled!\nDifferent row!");
		return;
	}
	double* temp;
	temp = (double*)mkl_malloc(row * (col + m.col) * sizeof(double), 64);
	for (unsigned int i = 0; i < this->row; i++) {
		for(unsigned int j = 0; j < this->col; j++) {
			temp[(this->col + m.col) * i + j] = this->matrix_buffer[col * i + j];
		}
		for (unsigned int j = 0; j < m.col; j++) {
			temp[this->col + (this->col + m.col) * i + j] = m.matrix_buffer[m.col * i + j];
		}
	}
	this->col += m.col;
	mkl_free(matrix_buffer);
	matrix_buffer = temp;
}

void Matrix::row_stack(const Matrix& m)
{
	if (this->col != m.col) {
		printf("row_stack falled!\nDifferent col!");
		return;
	}
	double* temp;
	temp = (double*)mkl_malloc(col * (row + m.row) * sizeof(double), 64);
	memcpy(temp, this->matrix_buffer, row * col * sizeof(double));
	memcpy(temp + row * col, m.matrix_buffer, m.row * m.col * sizeof(double));
	this->row += m.row;
	mkl_free(matrix_buffer);
	matrix_buffer = temp;
}

void Matrix::show()
{
	for (unsigned int i = 0; i < row; i++) {
		for (unsigned int j = 0; j < col; j++) {
			printf("%f ", matrix_buffer[i * col + j]);
		}
		printf("\n");
	}
}

void Matrix::operator=(const Matrix& m)
{
	mkl_free(matrix_buffer);
	this->row = m.row; this->col = m.col;
	matrix_buffer = (double*)mkl_malloc(row * col * sizeof(double), 64);
	if (matrix_buffer == NULL) {
		printf("\n ERROR: Can't allocate memory for matrices. Aborting... \n\n");
		mkl_free(matrix_buffer);
		return;
	}
	if (this->matrix_buffer == m.matrix_buffer) return;

	memcpy(this->matrix_buffer, m.matrix_buffer, row * col * sizeof(double));
}

Matrix Matrix::operator+(const Matrix& m)
{
	if (this->row != m.row or this->col != m.col) {
		printf("'+' Error! Different row or col\n");
		return NULL;
	}
	Matrix temp(m);
	cblas_daxpby(row*col, 1, this->matrix_buffer, 1, 1, temp.matrix_buffer, 1);
	return temp;
}

Matrix Matrix::operator-(const Matrix& m)
{
	if (this->row != m.row or this->col != m.col) {
		printf("'-' Error! Different row or col\n");
		return NULL;
	}
	Matrix temp(m);
	cblas_daxpby(row * col, 1, this->matrix_buffer, 1, -1, temp.matrix_buffer, 1);
	return temp;
}

Matrix Matrix::operator*(const Matrix& m)
{
	if (this->col != m.row) {
		printf("'*' Error! Incorrect row or col\n");
		return NULL;
	}
	Matrix temp(this->row, m.col);
	mkl_set_num_threads(mkl_get_max_threads());
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
		this->row, m.col, this->col, 1.0, this->matrix_buffer, this->col, m.matrix_buffer, m.col, 0.0, temp.matrix_buffer, m.col);
	return temp;
}
