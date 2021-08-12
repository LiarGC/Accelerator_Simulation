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
	for (unsigned int i = 0; i < row; i++) {
		for (unsigned int j = 0; j < col; j++) {
			if (sizeof_buffer > i * col + j) matrix_buffer[i * col + j] = buffer[i * col + j];
		}
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
	for (unsigned int i = 0; i < this->row; i++) {
		//matrix_buffer[i].insert(matrix_buffer[i].end(), m.matrix_buffer[i].begin(), m.matrix_buffer[i].end());
	}
	this->col += m.col;
}

void Matrix::row_stack(const Matrix& m)
{
	if (this->col != m.col) {
		printf("row_stack falled!\nDifferent col!");
		return;
	}
	for (unsigned int i = 0; i < m.row; i++) {
		//matrix_buffer.push_back(m.matrix_buffer[i]);
	}
	this->row += m.row;
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
	Matrix temp(this->row, this->col);
	for (unsigned int i = 0; i < this->row; i++) {
		for (unsigned int j = 0; j < this->col; j++) {
			temp.matrix_buffer[i * col + j] = this->matrix_buffer[i * col + j] + m.matrix_buffer[i * col + j];
		}
	}
	return temp;
}

Matrix Matrix::operator-(const Matrix& m)
{
	if (this->row != m.row or this->col != m.col) {
		printf("'-' Error! Different row or col\n");
		return NULL;
	}
	Matrix temp(this->row, this->col);
	for (unsigned int i = 0; i < this->row; i++) {
		for (unsigned int j = 0; j < this->col; j++) {
			temp.matrix_buffer[i * col + j] = this->matrix_buffer[i * col + j] - m.matrix_buffer[i * col + j];
		}
	}
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
