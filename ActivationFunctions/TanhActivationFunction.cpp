#include "TanhActivationFunction.h"

using namespace std;

const string TanhActivationFunction::name = "TanhActivationFunction";

double TanhActivationFunction::getActivation(double x) const
{
	return tanh(x);
}

double TanhActivationFunction::getDerivative(double x) const
{
	return 1 - tanh(x) * tanh(x);
}

string TanhActivationFunction::getName() const
{
	return name;
}