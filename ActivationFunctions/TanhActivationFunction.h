#include "ActivationFunction.h"
#include <cmath>

using namespace std;

class TanhActivationFunction: public ActivationFunction
{
public:
	double getActivation(double x) const;
	double getDerivative(double x) const;
};