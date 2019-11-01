#pragma once

#include <iostream>
#include <cxxabi.h>

using namespace std;

class LossFunction
{
public:
	virtual double getLoss(double x, double y) const = 0;
	virtual double getDerivative(double x, double y) const = 0;
};


ostream& operator <<(ostream &out, const LossFunction &loss_function);