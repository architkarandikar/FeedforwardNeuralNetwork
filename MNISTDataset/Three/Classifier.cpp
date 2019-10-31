#include "../../ActivationFunctions/ReluActivationFunction.h"
#include "../../ActivationFunctions/LeakyReluActivationFunction.h"
#include "../../ActivationFunctions/TanhActivationFunction.h"
#include "../../ActivationFunctions/LinearActivationFunction.h"
#include "../../ActivationFunctions/SigmoidActivationFunction.h"
#include "../../LossFunctions/SquaredErrorLossFunction.h"
#include "../../NeuronWeightInitializers/UniformlyRandomNeuronWeightInitializer.h"
#include "../../Datasets/Dataset.h"
#include "../../NeuralNetwork/NeuralNetwork.h"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

const int num_epochs = 1;

int main()
{
	srand(time(NULL)); rand();

	ReluActivationFunction relu_activation_function;
	LeakyReluActivationFunction leaky_relu_activation_function;
	TanhActivationFunction tanh_activation_function;
	LinearActivationFunction linear_activation_function;
	SigmoidActivationFunction sigmoid_activation_function;
	SquaredErrorLossFunction squared_error_loss_function;
	UniformlyRandomNeuronWeightInitializer uniformly_random_neuron_weight_initializer(0.0, 0.0001);

	Layer layers_array[2] = {
		Layer(784, 200, 0.001, leaky_relu_activation_function, uniformly_random_neuron_weight_initializer),
		Layer(200, 1, 0.001, sigmoid_activation_function, uniformly_random_neuron_weight_initializer)
	};
	vector<Layer> layers(layers_array, layers_array + 2);

	NeuralNetwork neuralNetwork(784, layers, squared_error_loss_function);

	Dataset training_dataset("training.data");
	cout<<"--------\n";
	cout<<"### Dataset loaded\n";
	cout<<"--------\n";
	vector<double> training_losses = neuralNetwork.train(training_dataset, num_epochs);
	cout<<"--------\n";
	for(int i = 0; i < num_epochs; ++i)
	{
		cout<<"Average Loss for Epoch #"<<i<<": "<<training_losses[i]<<"\n";
	}
	cout<<"--------\n";
	Dataset test_dataset("test.data");
	cout<<"Test Loss: "<<neuralNetwork.test(test_dataset)<<"\n";
	cout<<"--------\n";

	ofstream fout;
	fout.open("tmp_op.txt");
	for(int i = 0; i < test_dataset.getNumSamples(); ++i)
	{
		double label = test_dataset.getLabel(i);
		vector<double> feature_vector = test_dataset.getFeatureVector(i);
		double eval = neuralNetwork.evaluate(feature_vector);

		fout<<"Test example #"<<i<<":: \n";
		fout<<"Prediction: "<<eval<<" Label: "<<label<<"\n";
		fout<<"--------\n";
		for(int x = 0; x < 28; ++x)
		{
			for(int y = 0; y < 28; ++y)
				fout<<setfill('0')<<setw(3)<<(int)(feature_vector[28 * x + y] + 0.1);
			fout<<"\n";
		}
		fout<<"--------\n";
	}
}