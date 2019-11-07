#include "SquaredErrorLossFunction.h"

using namespace std;

const string SquaredErrorLossFunction::name = "SquaredErrorLossFunction";

double SquaredErrorLossFunction::getLoss(double x, double y) const
{
	return (x - y) * (x - y);
}

double SquaredErrorLossFunction::getDerivative(double x, double y) const
{
	return 2 * (x - y);
}

string SquaredErrorLossFunction::getName() const
{
	return name;
}