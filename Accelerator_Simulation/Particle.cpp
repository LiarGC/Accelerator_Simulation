#include "Particle.h"
#include "PhysicalParameter.h"
#include <math.h>

Particle::Particle()
{
	x = 0; y = 0; s = 0;
}

void Particle::SetPosition(double x, double y, double s)
{
	this->x = x;
	this->y = y;
	this->s = s;
}



void Particle::SetEk(double Ek)
{
	this->Ek = Ek;
	this->gamma = (E0 + Ek) / E0;
	this->relativistic_mass = gamma * rest_mass;
	this->beta = sqrt(1 - 1 / gamma / gamma);
	this->velocity = beta * c;
	this->Momentum = relativistic_mass * velocity;
	this->B_rho = Momentum / Charge;
}

void Particle::SetE_totall(double E_totall)
{
	if (E_totall < this->E0) return;
	SetEk(E_totall - this->E0);
}

void Particle::SetMomentum(double P)
{
	double Ek = c * sqrt(rest_mass * rest_mass * c * c + P * P) - E0;
	SetEk(Ek);
}

void Particle::SetB_rho(double B_rho)
{
	SetMomentum(B_rho * Charge);
}

void Particle::SetCharge(double Charge)
{
	this->Charge = Charge;
}

double Particle::GetGamma()
{
	return gamma;
}

double Particle::GetBeta()
{
	return beta;
}

double Particle::GetRelativistic_mass()
{
	return relativistic_mass;
}

double Particle::GetRest_mass()
{
	return rest_mass;
}

double Particle::GetVelocity()
{
	return velocity;
}

double Particle::GetEk()
{
	return Ek;
}

double Particle::GetE0()
{
	return E0;
}

double Particle::GetMomentum()
{
	return Momentum;
}

double Particle::GetCharge()
{
	return Charge;
}

double Particle::GetB_rho()
{
	return B_rho;
}

double Particle::Get_x()
{
	return x;
}

double Particle::Get_y()
{
	return y;
}

double Particle::Get_s()
{
	return s;
}

void Particle::SubInitial()
{
	this->SetRestMass();
	E0 = rest_mass * c * c;//J
	this->SetInitialCharge();
}

string Particle::GetClassName() const
{
	return typeid(*this).name();
}

Electron::Electron()
{
	SubInitial();
}

void Electron::SetRestMass()
{
	rest_mass = 9.10956E-31;
}

void Electron::SetInitialCharge()
{
	SetCharge(-1 * e);
}

REGISTER_cpp(Electron);

Proton::Proton()
{
	SubInitial();
}

void Proton::SetRestMass()
{
	rest_mass = 1.6726231E-27;
}

void Proton::SetInitialCharge()
{
	SetCharge(1 * e);
}

REGISTER_cpp(Proton);