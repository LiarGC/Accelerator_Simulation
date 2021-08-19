#include "Accelerator_Element.h"
#include "PhysicalParameter.h"

void Drift::CalculateTransferMatrix()
{
	double gamma = this->p_beam->p_IdealParticle->GetGamma();
	double buffer[36] = {
		1.0,	length,	0,		0,		0,		0,
		0,		1.0,	0,		0,		0,		0,
		0,		0,		1.,		length,	0,		0,
		0,		0,		0,		1.0,	0,		0,
		0,		0,		0,		0,		1,		length / gamma / gamma,
		0,		0,		0,		0,		0,		1
	};
	TransferMatrix.InputMatrixBuffer(buffer, sizeof(buffer));
}

void Drift::CalculateThroughB()
{
}

void Drift::CalculateThroughg()
{
}

void Accelerator_Element::SetLength(double length)
{
	this->length = length;
}

void Accelerator_Element::SetBeam(Beam& beam)
{
	this->p_beam = &beam;
}

Matrix& Accelerator_Element::GetTransferMatrix()
{
	CalculateTransferMatrix();
	return TransferMatrix;
}

void Bend::SetTheta(double Theta)
{
	this->Theta = Theta;
	this->rho = this->length / Theta;
	this->B = - p_beam->p_IdealParticle->GetB_rho() / this->rho;
	this->n = - rho / B * g;
}

void Accelerator_Element::SetB(double B)
{
	this->B = B;
	CalculateThroughB();
}

void Accelerator_Element::Set_g(double g)
{
	this->g = g;
	CalculateThroughg();
}

void SBend::CalculateTransferMatrix()
{
	double Kx = sqrt((1 - n) / rho / rho), Ky = sqrt(n / rho / rho);
	double temp1 = Kx * length, temp2 = Ky * length;
	double gamma = p_beam->p_IdealParticle->GetGamma();
	double beta = p_beam->p_IdealParticle->GetBeta();
	if (Ky != 0) {
		double buffer[36] = {
			cos(temp1),				sin(temp1) / Kx,					0,					0,				0,		(1 - cos(temp1)) / rho / Kx / Kx,
			-Kx * sin(temp1),		cos(temp1),							0,					0,				0,		sin(temp1) / rho / Kx,
			0,						0,									cos(temp2),			sin(temp2) / Ky,0,		0,
			0,						0,									-Ky * sin(temp2),	cos(temp2),		0,		0,
			-sin(temp1) / rho / Kx,	-(1 - cos(temp1)) / rho / Kx / Kx,	0,					0,				1,		-((1 - rho * rho * Kx * Kx / gamma / gamma) * length - sin(temp1) / Kx) / rho / rho / Kx / Kx,
			0,						0,									0,					0,				0,		1
		};
		TransferMatrix.InputMatrixBuffer(buffer, sizeof(buffer));
	}
	else
	{
		double buffer[36] = {
			cos(Theta),			sin(Theta) * rho,			0,				0,				0,		(1 - cos(Theta)) * rho,
			-sin(Theta)/rho,	cos(Theta),					0,				0,				0,		sin(Theta),
			0,					0,							1,				length,			0,		0,
			0,					0,							0,				1,				0,		0,
			-sin(Theta),		-(1 - cos(Theta)) * rho,	0,				0,				1,		sin(Theta)* rho - beta * beta * length,
			0,					0,							0,				0,				0,		1
		};
		TransferMatrix.InputMatrixBuffer(buffer, sizeof(buffer));
	}
}

void Bend::CalculateThroughB()
{
	SetTheta(- B * length / p_beam->p_IdealParticle->GetB_rho());
}

void Bend::CalculateThroughg()
{
	this->n = - rho / B * g;
}

void Quad::Setk_Mquad(double k_Mquad)
{
	this->k_Mquad = k_Mquad;
}

void Quad::CalculateTransferMatrix()
{
	double gamma = this->p_beam->p_IdealParticle->GetGamma();
	if (k_Mquad < 0) {
		double K = sqrt(-k_Mquad);
		double temp = K * length;
		double buffer[36] = {
			cos(temp),		sin(temp)/K,	0,				0,				0,		0,
			-K*sin(temp),	cos(temp),		0,				0,				0,		0,
			0,				0,				cosh(temp),		sinh(temp)/K,	0,		0,
			0,				0,				K*sinh(temp),	cosh(temp),		0,		0,
			0,				0,				0,				0,				1,		length / gamma / gamma,
			0,				0,				0,				0,				0,		1
		};
		TransferMatrix.InputMatrixBuffer(buffer, sizeof(buffer));
	}
	else {
		double K = sqrt(k_Mquad);
		double temp = K * length;
		double buffer[36] = {
			cosh(temp),		sinh(temp) / K,	0,				0,				0,		0,
			K * sinh(temp),	cosh(temp),		0,				0,				0,		0,
			0,				0,				cos(temp),		sin(temp) / K,	0,		0,
			0,				0,				-K * sin(temp),	cos(temp),		0,		0,
			0,				0,				0,				0,				1,		length / gamma / gamma,
			0,				0,				0,				0,				0,		1
		};
		TransferMatrix.InputMatrixBuffer(buffer, sizeof(buffer));
	}
}

void Quad::CalculateThroughB()
{
}

void Quad::CalculateThroughg()
{
	k_Mquad = g / p_beam->p_IdealParticle->GetB_rho();
}

void RBend::CalculateTransferMatrix()
{
	double Kx = sqrt((1 - n) / rho / rho), Ky = sqrt(n / rho / rho);
	double temp1 = Kx * length, temp2 = Ky * length;
	double gamma = p_beam->p_IdealParticle->GetGamma();
	double beta = p_beam->p_IdealParticle->GetBeta();
	Matrix temp_SBend(6, 6);
	if (Ky != 0) {
		double buffer[36] = {
			cos(temp1),				sin(temp1) / Kx,					0,					0,				0,		(1 - cos(temp1)) / rho / Kx / Kx,
			-Kx * sin(temp1),		cos(temp1),							0,					0,				0,		sin(temp1) / rho / Kx,
			0,						0,									cos(temp2),			sin(temp2) / Ky,0,		0,
			0,						0,									-Ky * sin(temp2),	cos(temp2),		0,		0,
			-sin(temp1) / rho / Kx,	-(1 - cos(temp1)) / rho / Kx / Kx,	0,					0,				1,		-((1 - rho * rho * Kx * Kx / gamma / gamma) * length - sin(temp1) / Kx) / rho / rho / Kx / Kx,
			0,						0,									0,					0,				0,		1
		};
		temp_SBend.InputMatrixBuffer(buffer, sizeof(buffer));
	}
	else
	{
		double buffer[36] = {
			cos(Theta),			sin(Theta) * rho,			0,				0,				0,		(1 - cos(Theta)) * rho,
			-sin(Theta) / rho,	cos(Theta),					0,				0,				0,		sin(Theta),
			0,					0,							1,				length,			0,		0,
			0,					0,							0,				1,				0,		0,
			-sin(Theta),		-(1 - cos(Theta)) * rho,	0,				0,				1,		sin(Theta) * rho - beta * beta * length,
			0,					0,							0,				0,				0,		1
		};
		temp_SBend.InputMatrixBuffer(buffer, sizeof(buffer));
	}
	
	Matrix temp_Deflection(6, 6);
	double buffer2[36] = {
		1.0,						0.0,	0.0,							0.0,	0.0,	0.0,
		tan(0.5 * Theta) / rho,		1.0,	0.0,							0.0,	0.0,	0.0,
		0.0,						0.0,	1.0,							0.0,	0.0,	0.0,
		0.0,						0.0,	-tan(0.5 * Theta) / rho,		1.0,	0.0,	0.0,
		0.0,						0.0,	0.0,							0.0,	1.0,	0.0,
		0.0,						0.0,	0.0,							0.0,	0.0,	1.0
	};
	temp_Deflection.InputMatrixBuffer(buffer2, sizeof(buffer2));
	TransferMatrix = temp_Deflection * temp_SBend * temp_Deflection;
}
