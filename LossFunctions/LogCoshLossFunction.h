#include "LossFunction.h"
#include <cmath>

using namespace std;

class LogCoshLossFunction: public LossFunction
{
public:
	double getLoss(double x, double y) const;
	double getDerivative(double x, double y) const;
};