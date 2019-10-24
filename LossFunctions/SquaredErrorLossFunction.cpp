#include "SquaredErrorLossFunction.h"

using namespace std;

double SquaredErrorLossFunction::getLoss(double x, double y) const
{
	return (x - y) * (x - y);
}
double SquaredErrorLossFunction::getDerivative(double x, double y) const
{
	return 2 * (x - y);
}