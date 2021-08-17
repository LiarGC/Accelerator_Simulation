#include "Beam.h"
#include "PhysicalParameter.h"
#include <iostream>

Beam::Beam(const Particle& particle)
{
	p_IdealParticle = (Particle*)ClassFactory::getInstance().getClassByName(particle.GetClassName());
	p_IdealParticle->SetEk(1 * GeV);
}

Beam::~Beam()
{
	delete p_IdealParticle;
	for (unsigned int i = 0; i < v_p_particles.size(); i++)
	{
		delete v_p_particles[i];
	}
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

		Particle* temp = (Particle*)ClassFactory::getInstance().getClassByName(p_IdealParticle->GetClassName());
		temp->Particle::Particle(x, y);
		temp->SetMomentum(Momentum);

		v_p_particles.push_back(temp);
	}
}