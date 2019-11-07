#pragma once

#include "LossFunction.h"

using namespace std;

class SquaredErrorLossFunction: public LossFunction
{
public:
	double getLoss(double x, double y) const;
	double getDerivative(double x, double y) const;
	string getName() const;

	friend istream& operator >>(istream &in, shared_ptr<LossFunction> &loss_function_ptr);

private:
	static const string name;
};