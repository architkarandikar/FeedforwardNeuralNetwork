#include "TanhActivationFunction.h"
#include "ReluActivationFunction.h"
#include "LeakyReluActivationFunction.h"
#include "LinearActivationFunction.h"
#include "SigmoidActivationFunction.h"
#include "ActivationFunctionIO.h"
#include <cxxabi.h>
#include <fstream>

using namespace std;

ofstream fout;
ifstream fin;
int print_test_count;

void activationFunctionPrintTest(shared_ptr<ActivationFunction> af)
{
	cout<<"----------------------\n";
	cout<<af<<"\n----------------------\n";

	for(double i = -3.0; i <= 3.0; i += 0.5)
	{
		printf("%.1f :: %.5f :: %.5f\n", i, af->getActivation(1.0 * i), af->getDerivative(1.0 * i));
	}
	cout<<"----------------------\n";

	fout<<af<<"\n";
	++print_test_count;
}

int main()
{
	fout.open("tmp.txt");
	print_test_count = 0;
	activationFunctionPrintTest(make_shared<TanhActivationFunction>());
	activationFunctionPrintTest(make_shared<ReluActivationFunction>());
	activationFunctionPrintTest(make_shared<LeakyReluActivationFunction>());
	activationFunctionPrintTest(make_shared<LinearActivationFunction>());
	activationFunctionPrintTest(make_shared<SigmoidActivationFunction>());
	fout.close();

	fin.open("tmp.txt");
	shared_ptr<ActivationFunction> p;
	for (int i = 0; i < print_test_count; ++i)
	{
		fin>>p;
		cout<<p<<"\n";
	}
	fin.close();
	cout<<"----------------------\n";

	return 0;
}