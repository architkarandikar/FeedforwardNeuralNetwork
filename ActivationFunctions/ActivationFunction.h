#pragma once

#include <iostream>

using namespace std;

class ActivationFunction
{
public:
	virtual double getActivation(double x) const = 0;
	virtual double getDerivative(double x) const = 0;
	virtual string getName() const = 0;
};