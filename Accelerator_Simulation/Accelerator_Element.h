#pragma once
#include "Matrix.h"
#include "Beam.h"

class Accelerator_Element
{
public:
	void SetLength(double length);
	void SetB(double B);
	void SetGradient(double Gradient);

	Matrix& GetTransferMatrix();
	virtual double GetTheta();

	static void SetBeam(Beam& beam);
protected:
	Matrix TransferMatrix = Matrix(6, 6);
	virtual void CalculateThroughB() = 0;
	virtual void CalculateThroughGradient() = 0;

	double length;//m
	double B;//T
	double Gradient;// B' :T/m

	static Beam* p_beam;
private:
	virtual void CalculateTransferMatrix() = 0;
};

class Drift :public Accelerator_Element {
public:

private:
	virtual void CalculateTransferMatrix();
	virtual void CalculateThroughB();
	virtual void CalculateThroughGradient();
};

class Bend:public Accelerator_Element
{
public:
	void SetTheta(double Theta);
	virtual double GetTheta();

protected:
	double Theta;	//rad
	double rho;		//m
	double n;		// rho/B*B'

private:
	virtual void CalculateThroughB();
	virtual void CalculateThroughGradient();
};

class SBend :public Bend {
public:

private:
	virtual void CalculateTransferMatrix();
};
class RBend :public Bend {
public:
private:
	virtual void CalculateTransferMatrix();// not perfect
};

class Quad :public Accelerator_Element {
public:
	void SetNormalizedGradient(double NormalizedGradient);
	void SetRotation(double Rotation);

private:
	virtual void CalculateTransferMatrix();
	virtual void CalculateThroughB();
	virtual void CalculateThroughGradient();

	double NormalizedGradient;// -g/(B_rho):m^-2
	double Rotation = 0;// anticlockwise
};

class Solenoid :public Accelerator_Element {
public:

private:
	virtual void CalculateTransferMatrix();
	virtual void CalculateThroughB();
	virtual void CalculateThroughGradient();
};