#include "TanhActivationFunction.h"

using namespace std;

double TanhActivationFunction::getActivation(double x) const
{
	return tanh(x);
}
double TanhActivationFunction::getDerivative(double x) const
{
	return 1 - tanh(x) * tanh(x);
}