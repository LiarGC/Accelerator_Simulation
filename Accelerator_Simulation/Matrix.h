#pragma once
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
	
	Matrix col_stack(const Matrix& m) const;
	Matrix row_stack(const Matrix& m) const;
	Matrix Transpose() const;
	Matrix Inverse() const;

	void show();


	void operator=(const Matrix& m);
	Matrix operator+(const Matrix& m);
	Matrix operator-(const Matrix& m);
	Matrix operator*(const Matrix& m);
	Matrix operator*(const double& scale);//只能 matrix * scale
	friend Matrix operator*(const double& scale, const Matrix& m);//scale * matrix 的实现
	
private:
	unsigned int row, col=2;
	double* matrix_buffer;
};