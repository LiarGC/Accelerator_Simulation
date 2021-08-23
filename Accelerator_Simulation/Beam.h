#pragma once
#include "Particle.h"
#include "Matrix.h"
#include <vector>
#include <random>

class Beam
{
public:
	Beam();
	Beam(const Particle& particle);
	virtual ~Beam();

	void GenerateParticlesInNormalDistribution(unsigned int num,double sigma);//mean is given by Ideal Particle
	void SetParticle(const Particle& particle);
	void SetMomentumDispersion(double MomentumDispersion);
	void SetEmittance(double Emittance);

	Particle* p_IdealParticle;
	std::vector<Particle*> v_p_particles;
private:
	double MomentumDispersion;
	double Emittance;// pi * m * rad
	Matrix SigmaMatrix = Matrix(6,6);
};

