#include "LeakyReluActivationFunction.h"

using namespace std;

double LeakyReluActivationFunction::getActivation(double x) const
{
	return (x > 0.0 ? x : 0.01 * x);
}
double LeakyReluActivationFunction::getDerivative(double x) const
{
	return (x > 0.0 ? 1.0 : 0.01);
}