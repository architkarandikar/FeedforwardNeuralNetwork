#include "LossFunction.h"

using namespace std;

class SquaredErrorLossFunction: public LossFunction
{
public:
	double getLoss(double x, double y) const;
	double getDerivative(double x, double y) const;
};