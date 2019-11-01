#pragma once

#include <iostream>
#include <cxxabi.h>

using namespace std;

class ActivationFunction
{
public:
	virtual double getActivation(double x) const = 0;
	virtual double getDerivative(double x) const = 0;
};

ostream& operator <<(ostream &out, const ActivationFunction &activation_function);