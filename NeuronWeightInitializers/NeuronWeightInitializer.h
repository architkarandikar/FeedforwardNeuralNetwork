#pragma once

#include <iostream>

using namespace std;

class NeuronWeightInitializer
{
public:
	virtual double getWeight() const = 0;
	virtual double getBias() const = 0;
};