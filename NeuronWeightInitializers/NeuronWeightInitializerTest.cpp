#include "UniformlyRandomNeuronWeightInitializer.h"
#include "NeuronWeightInitializerIO.h"
#include <fstream>
#include <iostream>

using namespace std;

ofstream fout;
ifstream fin;
int print_test_count;

void neuronWeightInitializerPrintTest(shared_ptr<NeuronWeightInitializer> nwi)
{
	cout<<"----------------------\n";
	cout<<nwi<<"\n";
	cout<<"----------------------\n";
	cout<<"Weights: \n";
	for(int i = 0; i < 5; ++i)
		printf("%.4f ", nwi->getWeight());
	cout<<"\n";
	cout<<"Biases: \n";
	for(int i = 0; i < 5; ++i)
		printf("%.4f ", nwi->getBias());
	cout<<"\n";
	cout<<"----------------------\n";

	fout<<nwi<<"\n";
	++print_test_count;
}

int main()
{
	srand(time(NULL)); rand();
	
	fout.open("tmp.txt");
	print_test_count = 0;
	double l1=0.5, r1=0.7;
	neuronWeightInitializerPrintTest(make_shared<UniformlyRandomNeuronWeightInitializer>(l1, r1));
	double l2=-2.8, r2=-2.3;
	neuronWeightInitializerPrintTest(make_shared<UniformlyRandomNeuronWeightInitializer>(l2, r2));
	fout.close();

	fin.open("tmp.txt");
	shared_ptr<NeuronWeightInitializer> p;
	for (int i = 0; i < print_test_count; ++i)
	{
		fin>>p;
		cout<<p<<"\n";
	}
	fin.close();
	cout<<"----------------------\n";

	return 0;
}