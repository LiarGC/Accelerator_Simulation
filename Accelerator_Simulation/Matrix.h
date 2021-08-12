#pragma once
#include <vector>
#include "mkl.h"

using namespace std;

class Matrix
{
public:
	Matrix(unsigned int row = 2, unsigned int col = 2);
	Matrix(const Matrix& m);
	virtual ~Matrix();
	void InputMatrixBuffer(double* buffer, unsigned int sizeof_buffer);
	void SetMartrixElement(unsigned int row,unsigned int col, double num);
	void col_stack(const Matrix& m);
	void row_stack(const Matrix& m);
	void show();


	void operator=(const Matrix& m);
	Matrix operator+(const Matrix& m);
	Matrix operator-(const Matrix& m);
	Matrix operator*(const Matrix& m);
private:
	unsigned int row, col=2;
	double* matrix_buffer;
};