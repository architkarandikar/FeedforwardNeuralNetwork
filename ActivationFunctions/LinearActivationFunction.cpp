#include "LinearActivationFunction.h"

using namespace std;

double LinearActivationFunction::getActivation(double x) const
{
	return x;
}
double LinearActivationFunction::getDerivative(double x) const
{
	return 1.0;
}