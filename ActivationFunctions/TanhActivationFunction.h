#pragma once

#include "ActivationFunction.h"
#include <cmath>

using namespace std;

class TanhActivationFunction: public ActivationFunction
{
public:
	double getActivation(double x) const;
	double getDerivative(double x) const;
	string getName() const;

	friend istream& operator >>(istream &in, shared_ptr<ActivationFunction> &activation_function_ptr);

private:
	static const string name;
};