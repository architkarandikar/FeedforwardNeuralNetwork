#pragma once

#include <iostream>

using namespace std;

class NeuronWeightInitializer
{
public:
	virtual double getWeight() const = 0;
	virtual double getBias() const = 0;
	virtual ostream& print(ostream &out) const = 0;
};

ostream& operator <<(ostream &out, const NeuronWeightInitializer &neuron_weight_initializer);