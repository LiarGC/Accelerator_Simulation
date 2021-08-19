#pragma once
#include "Matrix.h"
#include "Beam.h"

class Accelerator_Element
{
public:
	void SetLength(double length);
	void SetB(double B);
	void Set_g(double g);
	void SetBeam(Beam& beam);

	Matrix& GetTransferMatrix();
protected:
	Matrix TransferMatrix = Matrix(6, 6);
	virtual void CalculateThroughB() = 0;
	virtual void CalculateThroughg() = 0;

	double length;//m
	double B;//T
	double g;// B' :T/m
	
	Beam* p_beam;
private:
	virtual void CalculateTransferMatrix() = 0;
};

class Drift :public Accelerator_Element {
public:

private:
	virtual void CalculateTransferMatrix();
	virtual void CalculateThroughB();
	virtual void CalculateThroughg();
};

class Bend:public Accelerator_Element
{
public:
	void SetTheta(double Theta);

protected:
	double Theta;	//rad
	double rho;		//m
	double n;		// rho/B*B'

private:
	virtual void CalculateThroughB();
	virtual void CalculateThroughg();
};

class SBend :public Bend {
public:

private:
	virtual void CalculateTransferMatrix();
};
class RBend :public Bend {
public:
private:
	virtual void CalculateTransferMatrix();
};

class Quad :public Accelerator_Element {
public:
	void Setk_Mquad(double k_Mquad);

private:
	virtual void CalculateTransferMatrix();
	virtual void CalculateThroughB();
	virtual void CalculateThroughg();

	double k_Mquad;// -g/(B_rho):m^-2
};