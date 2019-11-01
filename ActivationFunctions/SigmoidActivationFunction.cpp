#include "SigmoidActivationFunction.h"

using namespace std;

double SigmoidActivationFunction::getActivation(double x) const
{
	return (x >= 0 ? (1.0 / (1.0 + exp(-x))) : (exp(x) / (1.0 + exp(x))));
}

double SigmoidActivationFunction::getDerivative(double x) const
{
	return getActivation(x) * (1.0 - getActivation(x));
}