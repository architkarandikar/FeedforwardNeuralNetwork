#include "LogCoshLossFunction.h"

using namespace std;

const string LogCoshLossFunction::name = "LogCoshLossFunction";

double LogCoshLossFunction::getLoss(double x, double y) const
{
	return log(cosh(x - y));
}

double LogCoshLossFunction::getDerivative(double x, double y) const
{
	return sinh(x - y) / cosh(x - y);
}

string LogCoshLossFunction::getName() const
{
	return name;
}