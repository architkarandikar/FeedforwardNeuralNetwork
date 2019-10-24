#include "../ActivationFunctions/ReluActivationFunction.h"
#include "../ActivationFunctions/TanhActivationFunction.h"
#include "../LossFunctions/SquaredErrorLossFunction.h"
#include "NeuralNetwork.h"

using namespace std;

int main()
{
	srand(time(NULL)); rand();

	ReluActivationFunction relu_activation_function;
	TanhActivationFunction tanh_activation_function;
	SquaredErrorLossFunction squared_error_loss_function;

	Layer layers_array[2] = {
		Layer(5, 3, 0.1, relu_activation_function),
		Layer(3, 1, 0.1, tanh_activation_function)
	};
	vector<Layer> layers(layers_array, layers_array + 2);

	NeuralNetwork neuralNetwork(5, layers, squared_error_loss_function);

	cout<<"--------\n";
	neuralNetwork.printWeights();
	cout<<"--------\n";
	cout<<"Evaluate all -1s: "<<neuralNetwork.evaluate(vector<double>(5, -1.0))<<"\n";
	cout<<"Evaluate all 1s: "<<neuralNetwork.evaluate(vector<double>(5, 1.0))<<"\n";
	cout<<"Evaluate all 2s: "<<neuralNetwork.evaluate(vector<double>(5, 2.0))<<"\n";
	cout<<"--------\n";
	cout<<"Backpropagate several times with all 1s input and expected output 0, print weights and evaluate again.\n";
	cout<<"~~~~~~~~\n";
	cout<<"Evaluate all 1s: "<<neuralNetwork.evaluate(vector<double>(5, 1.0))<<"\n";
	cout<<"~~~~~~~~\n";
	for (int i = 0; i <= 300; ++i)
	{
		if (i % 50 == 0)
			cout<<"Backpropagation #"<<i<<"\n";
		neuralNetwork.backPropagate(0.0, vector<double>(5, 1.0));
		if (i % 50 == 0)
		{
			neuralNetwork.printWeights();
			cout<<"Evaluate all 1s: "<<neuralNetwork.evaluate(vector<double>(5, 1.0))<<"\n";
			cout<<"~~~~~~~~\n";
		}
	}
	cout<<"--------\n";
}