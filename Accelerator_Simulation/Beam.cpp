#include "Beam.h"
#include "PhysicalParameter.h"
#include <iostream>

Beam::Beam(Particle particle)
{
	p_IdealParticle = new Particle(particle);
	p_IdealParticle->SetEk(1 * GeV);
}

Beam::~Beam()
{
	delete p_IdealParticle;
}

void Beam::GenerateParticlesInNormalDistribution(unsigned int num, double sigma)
{

	std::default_random_engine generator(time(NULL));
	std::normal_distribution<double> gauss_distribution(0.0, sigma);
	std::normal_distribution<double> momentum_distribution(0.0, MomentumDispersion/3);
	for (unsigned int i = 0; i < num; i++)
	{
		double x = p_IdealParticle->Get_x() + gauss_distribution(generator);
		double y = p_IdealParticle->Get_y() + gauss_distribution(generator);
		double Momentum = (1 + momentum_distribution(generator)) * p_IdealParticle->GetMomentum();

		Particle particle(*p_IdealParticle);
		particle.Particle::Particle(x, y);
		particle.SetMomentum(Momentum);

		v_particles.push_back(particle);
	}
}