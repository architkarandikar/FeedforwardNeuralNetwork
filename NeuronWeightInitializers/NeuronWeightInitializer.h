#pragma once

#include <iostream>

using namespace std;

class NeuronWeightInitializer
{
public:
	virtual double getWeight() const = 0;
	virtual double getBias() const = 0;
	virtual string getName() const = 0;

	virtual ostream& outputAdditional(ostream &out) const = 0;
	virtual istream& inputAdditional(istream &in) = 0;
};