#include "../ActivationFunctions/ReluActivationFunction.h"
#include "../NeuronWeightInitializers/UniformlyRandomNeuronWeightInitializer.h"
#include "Neuron.h"
#include <fstream>

using namespace std;

int main()
{
	srand(time(NULL));
	
	//ReluActivationFunction reluActivationFunction;
	//UniformlyRandomNeuronWeightInitializer uniformlyRandomNeuronWeightInitializer(0.0, 1.0);
	double l = 0.0, r = 1.0;
	Neuron neuron(5, 0.1, make_shared<ReluActivationFunction>(), make_shared<UniformlyRandomNeuronWeightInitializer>(l, r));

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

	ofstream fout;
	fout.open("tmp.txt");
	fout<<neuron<<"\n";
	fout.close();

	Neuron deserialized_neuron;
	ifstream fin;
	fin.open("tmp.txt");
	fin>>deserialized_neuron;
	cout<<"Deserialized Neuron output:\n";
	cout<<deserialized_neuron<<"\n";
	cout<<"--------\n";
	fin.close();

	return 0;
}