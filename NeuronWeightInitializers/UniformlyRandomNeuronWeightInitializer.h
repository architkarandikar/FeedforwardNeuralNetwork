#pragma once

#include "NeuronWeightInitializer.h"

using namespace std;

class UniformlyRandomNeuronWeightInitializer: public NeuronWeightInitializer
{
public:
	UniformlyRandomNeuronWeightInitializer();
	UniformlyRandomNeuronWeightInitializer(double left_range, double right_range);

	double getWeight() const;
	double getBias() const;
	string getName() const;

	ostream& outputAdditional(ostream &out) const;
	istream& inputAdditional(istream &in);

	friend istream& operator >>(istream &in, shared_ptr<NeuronWeightInitializer> &neuron_weight_initialzer_ptr);

private:
	static const string name;
	double left_range_, right_range_;

	double uniformlyRandomInRange() const;
};