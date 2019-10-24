#include "SquaredErrorLossFunction.h"
#include "LogCoshLossFunction.h"

using namespace std;

void lossFunctionPrintTest(const LossFunction &lf, double ref)
{
	for(double i = -3.0; i <= 3.0; i += 0.5)
		printf("(%.1f,%.1f) :: %.10f :: %.10f\n", i, ref, lf.getLoss(1.0*i, ref), lf.getDerivative(1.0*i, ref));
	printf("\n\n----------------------\n\n");
}

int main()
{
	lossFunctionPrintTest(SquaredErrorLossFunction(), 1.0);
	lossFunctionPrintTest(LogCoshLossFunction(), 0.0);

	return 0;
}