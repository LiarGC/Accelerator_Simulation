#include "Matrix.h"
#include "mkl.h"
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
	if (row * col < length) memcpy(matrix_buffer, buffer, row * col * sizeof(double));
	else memcpy(matrix_buffer, buffer, length * sizeof(double));
}

void Matrix::SetMartrixElement(unsigned int row, unsigned int col, double num)
{
	if (row > this->row or col > this->col) {
		printf("SetMartrixElement falled!\nMatrix size exceeded!\n");
		return;
	}
	matrix_buffer[row * this->col + col] = num;
}

void Matrix::Scale(double scale)
{
	cblas_dscal(row * col, scale, this->matrix_buffer, 1);
}

Matrix Matrix::col_stack(const Matrix& m) const
{
	if (this->row != m.row) {
		printf("col_stack falled!\nDifferent row!\n");
		return NULL;
	}
	return (this->Transpose().row_stack(m.Transpose())).Transpose();
	
}

Matrix Matrix::row_stack(const Matrix& m) const
{
	if (this->col != m.col) {
		printf("row_stack falled!\nDifferent col!");
		return NULL;
	}
	Matrix temp(row + m.row, col);
	memcpy(temp.matrix_buffer, this->matrix_buffer, row * col * sizeof(double));
	memcpy(temp.matrix_buffer + row * col, m.matrix_buffer, m.row * m.col * sizeof(double));
	return temp;
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

Matrix Matrix::operator+(const Matrix& m) const
{
	if (this->row != m.row or this->col != m.col) {
		printf("'+' Error! Different row or col\n");
		return NULL;
	}
	Matrix temp(m);
	cblas_daxpby(row*col, 1, this->matrix_buffer, 1, 1, temp.matrix_buffer, 1);
	return temp;
}

Matrix Matrix::operator-(const Matrix& m) const
{
	if (this->row != m.row or this->col != m.col) {
		printf("'-' Error! Different row or col\n");
		return NULL;
	}
	Matrix temp(m);
	cblas_daxpby(row * col, 1, this->matrix_buffer, 1, -1, temp.matrix_buffer, 1);
	return temp;
}

Matrix Matrix::operator*(const Matrix& m) const
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

Matrix Matrix::operator*(const double& scale) const
{
	Matrix temp(*this);
	cblas_dscal(row * col, scale, temp.matrix_buffer, 1);
	return temp;
}

void Matrix::operator+=(const Matrix& m)
{
	if (this->row != m.row or this->col != m.col) {
		printf("'+=' Error! Different row or col\n");
		return;
	}
	cblas_daxpby(row * col, 1, m.matrix_buffer, 1, 1, this->matrix_buffer, 1);
}

void Matrix::operator-=(const Matrix& m)
{
	if (this->row != m.row or this->col != m.col) {
		printf("'-=' Error! Different row or col\n");
		return;
	}
	cblas_daxpby(row * col, 1, m.matrix_buffer, 1, -1, this->matrix_buffer, 1);
}

void Matrix::operator*=(const double& scale)
{
	cblas_dscal(row * col, scale, this->matrix_buffer, 1);
}

Matrix operator*(const double& scale, const Matrix& m)
{
	return m * scale;
}

Matrix Matrix::Transpose() const
{
	Matrix temp(*this);
	MKL_Dimatcopy('R', 'T', row, col, 1, temp.matrix_buffer, col, row);
	unsigned int temp1 = temp.row;
	temp.row = temp.col; temp.col = temp1;
	return temp;
}