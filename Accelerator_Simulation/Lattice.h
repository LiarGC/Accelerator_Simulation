#pragma once
#include "Accelerator_Element.h"
#include "Beam.h"
#include <vector>

using namespace std;

class Lattice
{
public:

	virtual ~Lattice();

	void SetParticle(const Particle& particle);
	void AddDriftAt(unsigned int order);

	Beam beam;
private:
	void CheckIfLatticeIsRing();
	bool IfLatticeIsRing;

	vector<Accelerator_Element*> v_p_AcceleratorElements;
	vector<double> v_Betas;

};

