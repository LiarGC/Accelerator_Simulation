#pragma once
#include "Particle.h"
#include <vector>
#include <random>

class Beam
{
public:
	Beam(Particle particle);
	virtual ~Beam();
	Particle* p_IdealParticle;

	void GenerateParticlesInNormalDistribution(unsigned int num,double sigma);//mean is given by Ideal Particle


	std::vector<Particle> v_particles;
private:
	double MomentumDispersion = 0.001;
};

