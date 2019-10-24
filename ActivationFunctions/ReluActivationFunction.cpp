#include "ReluActivationFunction.h"

using namespace std;

double ReluActivationFunction::getActivation(double x) const
{
	return max(x, 0.0);
}
double ReluActivationFunction::getDerivative(double x) const
{
	return (x > 0.0 ? 1.0 : 0.0);
}