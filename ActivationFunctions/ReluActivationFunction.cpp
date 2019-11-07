#include "ReluActivationFunction.h"

using namespace std;

const string ReluActivationFunction::name = "ReluActivationFunction";

double ReluActivationFunction::getActivation(double x) const
{
	return max(x, 0.0);
}

double ReluActivationFunction::getDerivative(double x) const
{
	return (x > 0.0 ? 1.0 : 0.0);
}

string ReluActivationFunction::getName() const
{
	return name;
}