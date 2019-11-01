#include "../ActivationFunctions/ReluActivationFunction.h"
#include "../NeuronWeightInitializers/UniformlyRandomNeuronWeightInitializer.h"
#include "Neuron.h"

using namespace std;

int main()
{
	srand(time(NULL));
	
	ReluActivationFunction reluActivationFunction;
	UniformlyRandomNeuronWeightInitializer uniformlyRandomNeuronWeightInitializer(0.0, 1.0);
	Neuron neuron(5, 0.1, reluActivationFunction, uniformlyRandomNeuronWeightInitializer);

	cout<<"--------\n";
	cout<<"Neuron weights: "; neuron.printWeights();
	cout<<"--------\n";

	cout<<"Evaluate all -1s with Relu Activation: "<<neuron.evaluate(vector<double>(5, -1.0))<<"\n";
	cout<<"Evaluate all 1s with Relu Activation: "<<neuron.evaluate(vector<double>(5, 1.0))<<"\n";
	cout<<"Evaluate all 2s with Relu Activation: "<<neuron.evaluate(vector<double>(5, 2.0))<<"\n";
	cout<<"Neuron weights: "; neuron.printWeights();
	cout<<"--------\n";

	cout<<"Loss derivative wrt inputs with all 1s input and Loss WRT Outputs set to 1: ";
	vector<double> losses = neuron.getLossDerivativeWrtInputs(1.0, vector<double>(5, 1.0));
	for(int i = 0; i < 5; ++i)
	{
		cout<<losses[i]<<" ";
	}
	cout<<"\n";
	cout<<"Backpropagate with all 1s input and Loss WRT Outputs set to 1.\n";
	neuron.backPropagate(1.0, vector<double>(5, 1.0));
	cout<<"Neuron weights: "; neuron.printWeights();
	cout<<"--------\n";

	cout<<"Loss derivative wrt inputs with all -1s input and Loss WRT Outputs set to 1: ";
	losses = neuron.getLossDerivativeWrtInputs(1.0, vector<double>(5, -1.0));
	for(int i = 0; i < 5; ++i)
	{
		cout<<losses[i]<<" ";
	}
	cout<<"\n";
	cout<<"Backpropagate with all -1s input and Loss WRT Outputs set to 1.\n";
	neuron.backPropagate(1.0, vector<double>(5, -1.0));
	cout<<"Neuron weights: "; neuron.printWeights();
	cout<<"--------\n";

	cout<<"Neuron output:\n";
	cout<<neuron<<"\n";
	cout<<"--------\n";

	return 0;
}