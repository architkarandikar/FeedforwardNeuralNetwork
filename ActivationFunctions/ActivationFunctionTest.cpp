#include "TanhActivationFunction.h"
#include "ReluActivationFunction.h"
#include "LeakyReluActivationFunction.h"
#include "LinearActivationFunction.h"
#include "SigmoidActivationFunction.h"

using namespace std;

void activationFunctionPrintTest(const ActivationFunction &af)
{
	for(double i = -3.0; i <= 3.0; i += 0.5)
		printf("%.1f :: %.10f :: %.10f\n", i, af.getActivation(1.0*i), af.getDerivative(1.0*i));
	printf("\n\n----------------------\n\n");
}

int main()
{
	activationFunctionPrintTest(TanhActivationFunction());
	activationFunctionPrintTest(ReluActivationFunction());
	activationFunctionPrintTest(LeakyReluActivationFunction());
	activationFunctionPrintTest(LinearActivationFunction());
	activationFunctionPrintTest(SigmoidActivationFunction());

	return 0;
}