#include "Lattice.h"
#include "PhysicalParameter.h"

Lattice::~Lattice()
{
	for (unsigned int i = 0; i < v_p_AcceleratorElements.size(); i++)
	{
		delete v_p_AcceleratorElements[i];
	}
}

void Lattice::SetParticle(const Particle& particle)
{
	beam.SetParticle(particle);
	Accelerator_Element::SetBeam(beam);
}

void Lattice::AddDriftAt(unsigned int order)
{
	Drift* temp = new Drift;
	v_p_AcceleratorElements.insert(v_p_AcceleratorElements.begin() + order, temp);
	CheckIfLatticeIsRing();
}

void Lattice::CheckIfLatticeIsRing()
{
	double sum = 0;
	for (unsigned int i = 0; i < v_p_AcceleratorElements.size(); i++)
	{
		sum += v_p_AcceleratorElements[i]->GetTheta();
	}
	if (sum == 2 * pi) IfLatticeIsRing = 1;
	else IfLatticeIsRing = 0;
	if (sum > 2 * pi) printf("Error! Total Theta is more than 2 pi\n");
}
