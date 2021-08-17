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

	Matrix GetTransferMatrix();
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
	Drift(double length = 1.0);
private:
	virtual void CalculateTransferMatrix();
	virtual void CalculateThroughB();
	virtual void CalculateThroughg();
};

class SBend :public Accelerator_Element {
public:
	SBend(double length = 1.0);

	void SetTheta(double Theta);
private:
	virtual void CalculateTransferMatrix();
	virtual void CalculateThroughB();
	virtual void CalculateThroughg();

	double Theta = 0;//rad
	double rho = 1;//m
	double n;// rho/B*B'
};

class Quad :public Accelerator_Element {
public:
	Quad(double length = 1.0);
	void Setk_Mquad(double k_Mquad);

private:
	virtual void CalculateTransferMatrix();
	virtual void CalculateThroughB();
	virtual void CalculateThroughg();

	double k_Mquad;// -g/(B_rho):m^-2
};