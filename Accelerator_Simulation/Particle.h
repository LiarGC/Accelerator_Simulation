#pragma once

class Particle
{
public:
	Particle();
	Particle(double x, double y);
	void SetEk(double Ek);
	void SetE_totall(double E0);
	void SetMomentum(double P);
	void SetB_rho(double B_rho);

	double GetGamma();
	double GetBeta();
	double GetRelativistic_mass();// kg
	double GetRest_mass();// kg
	double GetVelocity();// m/s
	double GetEk();// J
	double GetE0();// J
	double GetMomentum();// kg*m/s
	double GetCharge();// C
	double GetB_rho();//T*m

	double Get_x();//m
	double Get_y();//m
	double Get_s();//m

protected:
	void SetRest_mass(double rest_mass);// kg
	void SetCharge(double Charge);// C
private:
	double relativistic_mass, rest_mass;// kg
	double beta, gamma;
	double velocity;// m/s
	double Ek, E0;// J
	double Momentum;// kg*m/s
	double Charge;// C
	double B_rho;//T*m

	double x, y, s;
};

class Electron :public Particle 
{
public:
	Electron();
	Electron(double x, double y);
};

class Proton :public Particle
{
public:
	Proton();
	Proton(double x, double y);
};