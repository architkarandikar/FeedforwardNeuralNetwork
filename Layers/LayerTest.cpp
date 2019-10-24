#include "../ActivationFunctions/ReluActivationFunction.h"
#include "../NeuronWeightInitializers/UniformlyRandomNeuronWeightInitializer.h"
#include "Layer.h"

using namespace std;

int main()
{
	srand(time(NULL));

	ReluActivationFunction reluActivationFunction;
	UniformlyRandomNeuronWeightInitializer uniformlyRandomNeuronWeightInitializer(0.0, 1.0);
	Layer layer(5, 3, 0.1, reluActivationFunction, uniformlyRandomNeuronWeightInitializer);

	cout<<"--------\n";
	cout<<"In Degree: "<<layer.getInDegree()<<", Out Degree: "<<layer.getOutDegree()<<"\n";
	cout<<"Layer weights:\n"; layer.printWeights();
	cout<<"--------\n";

	vector<double> evaluation = layer.evaluate(vector<double>(5, -1.0));
	cout<<"Evaluate all -1s: ";
	for(int i = 0; i < 3; ++i)
	{
		cout<<evaluation[i]<<" ";
	}
	cout<<"\n";
	evaluation = layer.evaluate(vector<double>(5, 1.0));
	cout<<"Evaluate all 1s: ";
	for(int i = 0; i < 3; ++i)
	{
		cout<<evaluation[i]<<" ";
	}
	cout<<"\n";
	evaluation = layer.evaluate(vector<double>(5, 2.0));
	cout<<"Evaluate all 2s: ";
	for(int i = 0; i < 3; ++i)
	{
		cout<<evaluation[i]<<" ";
	}
	cout<<"\n";
	cout<<"Layer weights:\n"; layer.printWeights();
	cout<<"--------\n";

	cout<<"Loss derivative wrt inputs with all 1s input and Loss WRT Outputs set to all 1s: ";
	vector<double> losses = layer.getLossDerivativeWrtInputs(vector<double>(3, 1.0), vector<double>(5, 1.0));
	for(int i = 0; i < 5; ++i)
	{
		cout<<losses[i]<<" ";
	}
	cout<<"\n";
	cout<<"Backpropagate with all 1s input and Loss WRT Outputs set to all 1s.\n";
	layer.backPropagate(vector<double>(3, 1.0), vector<double>(5, 1.0));
	cout<<"Layer weights:\n"; layer.printWeights();
	cout<<"--------\n";

	return 0;
}