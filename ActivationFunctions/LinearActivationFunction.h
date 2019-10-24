#include "ActivationFunction.h"

using namespace std;

class LinearActivationFunction: public ActivationFunction
{
public:
	double getActivation(double x) const;
	double getDerivative(double x) const;
};