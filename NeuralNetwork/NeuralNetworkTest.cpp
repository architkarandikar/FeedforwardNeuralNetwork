#include "../ActivationFunctions/ReluActivationFunction.h"
#include "../ActivationFunctions/TanhActivationFunction.h"
#include "../LossFunctions/SquaredErrorLossFunction.h"
#include "../NeuronWeightInitializers/UniformlyRandomNeuronWeightInitializer.h"
#include "NeuralNetwork.h"
#include <fstream>

using namespace std;

int main()
{
	srand(time(NULL)); rand();

	double l = 0.0, r = 1.0;
	Layer layers_array[2] = {
		Layer(5, 3, 0.1, make_shared<ReluActivationFunction>(), make_shared<UniformlyRandomNeuronWeightInitializer>(l, r)),
		Layer(3, 1, 0.1, make_shared<TanhActivationFunction>(), make_shared<UniformlyRandomNeuronWeightInitializer>(l, r))
	};
	vector<Layer> layers(layers_array, layers_array + 2);

	NeuralNetwork neural_network(5, layers, make_shared<SquaredErrorLossFunction>());

	cout<<"--------\n";
	neural_network.printWeights();
	cout<<"--------\n";
	cout<<"Evaluate all -1s: "<<neural_network.evaluate(vector<double>(5, -1.0))<<"\n";
	cout<<"Evaluate all 1s: "<<neural_network.evaluate(vector<double>(5, 1.0))<<"\n";
	cout<<"Evaluate all 2s: "<<neural_network.evaluate(vector<double>(5, 2.0))<<"\n";
	cout<<"--------\n";
	cout<<"Backpropagate several times with all 1s input and expected output 0, print weights and evaluate again.\n";
	cout<<"~~~~~~~~\n";
	cout<<"Evaluate all 1s: "<<neural_network.evaluate(vector<double>(5, 1.0))<<"\n";
	cout<<"~~~~~~~~\n";
	for (int i = 0; i <= 500; ++i)
	{
		if (i % 50 == 0)
			cout<<"Backpropagation #"<<i<<"\n";
		neural_network.backPropagate(0.0, vector<double>(5, 1.0));
		if (i % 50 == 0)
		{
			neural_network.printWeights();
			cout<<"Evaluate all 1s: "<<neural_network.evaluate(vector<double>(5, 1.0))<<"\n";
			cout<<"~~~~~~~~\n";
		}
	}
	cout<<"--------\n";
	cout<<"Neural Network Output:\n";
	cout<<neural_network<<"\n";
	cout<<"--------\n";

	ofstream fout;
	fout.open("tmp.txt");
	fout<<neural_network<<"\n";
	fout.close();

	NeuralNetwork deserialized_neural_network;
	ifstream fin;
	fin.open("tmp.txt");
	fin>>deserialized_neural_network;
	cout<<"Deserialized Neural Network output:\n";
	cout<<deserialized_neural_network<<"\n";
	cout<<"--------\n";
	fin.close();
}