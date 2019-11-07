#include "LinearActivationFunction.h"

using namespace std;

const string LinearActivationFunction::name = "LinearActivationFunction";

double LinearActivationFunction::getActivation(double x) const
{
	return x;
}

double LinearActivationFunction::getDerivative(double x) const
{
	return 1.0;
}

string LinearActivationFunction::getName() const
{
	return name;
}