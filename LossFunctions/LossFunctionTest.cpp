#include "SquaredErrorLossFunction.h"
#include "LogCoshLossFunction.h"
#include "LossFunctionIO.h"
#include <fstream>

using namespace std;

ofstream fout;
ifstream fin;
int print_test_count;

void lossFunctionPrintTest(shared_ptr<LossFunction> lf, double ref)
{
	printf("----------------------\n");
	cout<<lf<<"\n----------------------\n";

	for(double i = -3.0; i <= 3.0; i += 0.5)
	{
		printf("(%.1f,%.1f) :: %.10f :: %.10f\n", i, ref, lf->getLoss(1.0 * i, ref), lf->getDerivative(1.0 * i, ref));
	}
	printf("----------------------\n");

	fout<<lf<<"\n";
	++print_test_count;
}

int main()
{
	fout.open("tmp.txt");
	print_test_count = 0;
	lossFunctionPrintTest(make_shared<SquaredErrorLossFunction>(), 1.0);
	lossFunctionPrintTest(make_shared<LogCoshLossFunction>(), 0.0);
	fout.close();

	fin.open("tmp.txt");
	shared_ptr<LossFunction> p;
	for (int i = 0; i < print_test_count; ++i)
	{
		fin>>p;
		cout<<p<<"\n";
	}
	fin.close();
	cout<<"----------------------\n";

	return 0;
}