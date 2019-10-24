#pragma once

#include <iostream>

using namespace std;

class LossFunction
{
public:
	virtual double getLoss(double x, double y) const = 0;
	virtual double getDerivative(double x, double y) const = 0;
};