#include "UniformlyRandomNeuronWeightInitializer.h"

using namespace std;

void neuronWeightInitializerPrintTest(const NeuronWeightInitializer &nwi)
{
	cout<<"Weights: \n";
	for(int i = 0; i < 5; ++i)
		printf("%.4f ", nwi.getWeight());
	cout<<"\n";
	cout<<"Biases: \n";
	for(int i = 0; i < 5; ++i)
		printf("%.4f ", nwi.getBias());
	cout<<"\n\n";
}

int main()
{
	srand(time(NULL)); rand();
	
	neuronWeightInitializerPrintTest(UniformlyRandomNeuronWeightInitializer(0.5, 0.7));
	neuronWeightInitializerPrintTest(UniformlyRandomNeuronWeightInitializer(-2.3, -2.8));

	return 0;
}